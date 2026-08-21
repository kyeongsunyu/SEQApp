# IPC ABI check (Win32 vs x64)

SEQApp does not own its wire formats. It shares them with other processes:

| channel | struct | header |
| --- | --- | --- |
| named shared memory `/SMEMORY` | `TMemCommand` | `SEQApp/Func/SharedMemBase.h` |
| memory-mapped file | `_MMF` | `SEQApp/Func/NVMMF.h` |
| `WM_COPYDATA` to `MMIApp` | `SEQ_RSP`, `SEQ_LOG`, … | `SEQApp/SeqMain/Define/DEFINE_WinMsg.h` |
| vision TCP protocol | `VISION_*` | `SEQApp/SeqMain/Define/DEFINE_Data.h` |

Building SEQApp as x64 is only safe while `MMIApp` / `COMMUNICATION_App` are
still 32-bit if none of those structs changes size or field offset. `run.sh`
proves that: it parses the real headers twice with clang, once as
`i686-pc-windows-msvc` and once as `x86_64-pc-windows-msvc`, dumps every record
layout, and diffs the two.

```sh
tools/abi_check/run.sh
# OK: 80 record layouts are identical under the 32-bit and 64-bit MSVC ABI.
```

Only clang is needed — the probe is parsed, never compiled or linked, so it runs
on any host. `stubinc/` holds a minimal `<windows.h>` with the MSVC scalar
widths; the implementation classes that hold `HANDLE`s and pointers are trimmed
off the extracted headers, since those never leave the process.

Run it again after touching any of the headers above. A `MISMATCH` means a
32-bit peer would read the fields at the wrong offsets.
