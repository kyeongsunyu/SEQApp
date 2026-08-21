#!/usr/bin/env bash
# Verifies that every struct SEQApp shares with another process (shared memory,
# the memory-mapped file, WM_COPYDATA payloads and the vision TCP protocol) has
# exactly the same layout under the 32-bit and the 64-bit MSVC ABI.
#
# This is what makes the Win32 -> x64 move safe while MMIApp / COMMUNICATION_App
# are still 32-bit: the wire format must not move a single byte.
#
# Requires clang (any host OS); it only parses, it never links.
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$(cd "$here/../.." && pwd)"
gen="$here/gen"
mkdir -p "$gen"

# MSVC keeps `long` at 32 bits on x64; clang targeting *-windows-msvc does the
# same, so no rewriting is needed for the target itself. The extracted copies
# below only drop the parts of the headers that are implementation (classes
# holding HANDLEs and pointers), keeping the wire structs.
extract() { # <source header> <first line of the trailing class> <output>
	local src="$1" marker="$2" out="$3"
	local cut
	cut="$(grep -n "$marker" "$src" | head -1 | cut -d: -f1)"
	head -n "$((cut - 1))" "$src" > "$out"
	printf '\n#pragma pack(pop)\n' >> "$out"
	# re-close whatever include guard / #if the truncation left open
	local opened closed
	opened="$(grep -cE '^[[:space:]]*#[[:space:]]*(if|ifdef|ifndef)\b' "$out" || true)"
	closed="$(grep -cE '^[[:space:]]*#[[:space:]]*endif\b' "$out" || true)"
	for ((i = closed; i < opened; i++)); do printf '#endif\n' >> "$out"; done
}

extract "$root/SEQApp/Func/SharedMemBase.h" 'class SHARED_MEMORY_BASE' "$gen/wire_shm.h"
extract "$root/SEQApp/Func/NVMMF.h"         'class CNVMMF'             "$gen/wire_nvmmf.h"

dump() { # <target triple>
	clang++ -target "$1" -std=c++17 -nostdinc++ -nostdlibinc \
		-I "$here/stubinc" -I "$here" -I "$root/SEQApp/SeqMain/Define" \
		-fsyntax-only -Xclang -fdump-record-layouts "$here/abi_probe.cpp" 2>&1 |
		grep -E '^\s*\|?\s*(\[sizeof=|[0-9]+ \| )' |
		sed -E 's/[[:space:]]+/ /g; s/^ //'
}

dump i686-pc-windows-msvc   > "$gen/layout-x86.txt"
dump x86_64-pc-windows-msvc > "$gen/layout-x64.txt"

if diff -u "$gen/layout-x86.txt" "$gen/layout-x64.txt" > "$gen/layout.diff"; then
	echo "OK: $(grep -c '\[sizeof=' "$gen/layout-x64.txt") record layouts are identical under the 32-bit and 64-bit MSVC ABI."
else
	echo "MISMATCH: the 32-bit and 64-bit layouts differ. See $gen/layout.diff"
	cat "$gen/layout.diff"
	exit 1
fi
