#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Line-scan inspection machine - 1 axis encoder trigger
Electrical schematic generator -> DXF R12 ASCII (A3 landscape, 420 x 297 mm)

Sheets:
  1  System interconnection
  2  X4 command / status wiring  (Ajinextek motion board <-> MBDLT25SM)
  3  Trigger chain (encoder feedback -> SIO-HPC4L -> line scan camera)

Labels are ASCII only: DXF R12 has no reliable unicode code page, and Korean
text renders as garbage on CAD stations configured for a different code page.
"""

# ----------------------------------------------------------------- DXF writer

LAYERS = [
    # name,            aci color
    ("BORDER",          7),
    ("TITLE",           7),
    ("COMPONENT",       5),   # blue
    ("TERMINAL",        7),
    ("WIRE_PWR",        1),   # red    - AC / DC power
    ("WIRE_SIG",        3),   # green  - single ended signal
    ("WIRE_DIFF",       4),   # cyan   - differential pair
    ("WIRE_TRIG",       6),   # magenta- trigger
    ("TEXT",            7),
    ("TEXT_SMALL",      8),
    ("NOTE",            2),   # yellow
    ("DIM",             8),
]


class Dxf:
    def __init__(self):
        self.e = []

    # -- entities ---------------------------------------------------------
    def line(self, layer, x1, y1, x2, y2):
        self.e += ["0", "LINE", "8", layer,
                   "10", f"{x1:.3f}", "20", f"{y1:.3f}", "30", "0.0",
                   "11", f"{x2:.3f}", "21", f"{y2:.3f}", "31", "0.0"]

    def rect(self, layer, x, y, w, h):
        self.line(layer, x, y, x + w, y)
        self.line(layer, x + w, y, x + w, y + h)
        self.line(layer, x + w, y + h, x, y + h)
        self.line(layer, x, y + h, x, y)

    def circle(self, layer, x, y, r):
        self.e += ["0", "CIRCLE", "8", layer,
                   "10", f"{x:.3f}", "20", f"{y:.3f}", "30", "0.0",
                   "40", f"{r:.3f}"]

    def text(self, layer, x, y, h, s, halign=0, valign=0):
        """halign 0=left 1=center 2=right ; valign 0=base 1=bottom 2=mid 3=top"""
        self.e += ["0", "TEXT", "8", layer,
                   "10", f"{x:.3f}", "20", f"{y:.3f}", "30", "0.0",
                   "40", f"{h:.3f}", "1", s]
        if halign or valign:
            self.e += ["72", str(halign), "73", str(valign),
                       "11", f"{x:.3f}", "21", f"{y:.3f}", "31", "0.0"]

    # -- composites -------------------------------------------------------
    def poly(self, layer, pts):
        for a, b in zip(pts, pts[1:]):
            self.line(layer, a[0], a[1], b[0], b[1])

    def dot(self, layer, x, y, r=0.8):
        """junction dot"""
        self.circle(layer, x, y, r)
        self.circle(layer, x, y, r * 0.55)

    def arrow(self, layer, x, y, dx, dy, size=2.2):
        """simple open arrow head pointing along (dx,dy), unit-ish"""
        import math
        n = math.hypot(dx, dy) or 1.0
        ux, uy = dx / n, dy / n
        px, py = -uy, ux
        bx, by = x - ux * size, y - uy * size
        self.line(layer, x, y, bx + px * size * 0.45, by + py * size * 0.45)
        self.line(layer, x, y, bx - px * size * 0.45, by - py * size * 0.45)

    def block(self, x, y, w, h, title, sub=None, sub2=None):
        """component box with title"""
        self.rect("COMPONENT", x, y, w, h)
        self.line("COMPONENT", x, y + h - 7, x + w, y + h - 7)
        self.text("TEXT", x + w / 2, y + h - 5.0, 3.0, title, 1, 1)
        if sub:
            self.text("TEXT_SMALL", x + w / 2, y + h - 13, 2.4, sub, 1, 1)
        if sub2:
            self.text("TEXT_SMALL", x + w / 2, y + h - 18, 2.4, sub2, 1, 1)

    def term(self, x, y, label, side="l", h=2.2):
        """terminal pad + label. side = which side the label sits."""
        self.circle("TERMINAL", x, y, 0.9)
        if side == "l":
            self.text("TEXT_SMALL", x - 2.2, y, h, label, 2, 2)
        else:
            self.text("TEXT_SMALL", x + 2.2, y, h, label, 0, 2)

    # -- sheet furniture --------------------------------------------------
    def border_and_title(self, sheet_no, sheet_title, rev="Rev.2"):
        W, H = 420.0, 297.0
        self.rect("BORDER", 10, 10, W - 20, H - 20)
        self.rect("BORDER", 12, 12, W - 24, H - 24)

        # title block  (bottom-right)
        tx, ty, tw, th = 250.0, 12.0, 158.0, 44.0
        self.rect("TITLE", tx, ty, tw, th)
        for yy in (ty + 11, ty + 22, ty + 33):
            self.line("TITLE", tx, yy, tx + tw, yy)
        self.line("TITLE", tx + 100, ty, tx + 100, ty + 33)

        self.text("TITLE", tx + 3, ty + 37.0, 3.6,
                  "LINE SCAN INSPECTION  /  1-AXIS ENCODER TRIGGER")
        self.text("TITLE", tx + 3, ty + 26.0, 3.2, sheet_title)
        self.text("TEXT_SMALL", tx + 3, ty + 16.0, 2.4, "PROJECT : SEQApp")
        self.text("TEXT_SMALL", tx + 3, ty + 5.0, 2.4, "DRAWN   : (   )    CHK : (   )")
        self.text("TEXT_SMALL", tx + 103, ty + 16.0, 2.4, f"SHEET {sheet_no} OF 3")
        self.text("TEXT_SMALL", tx + 103, ty + 5.0, 2.4, f"{rev}   SIZE A3   DATE:(      )")

    def note_box(self, x, y, w, lines, title="NOTES"):
        h = 8.0 + 5.0 * len(lines)
        self.rect("NOTE", x, y, w, h)
        self.line("NOTE", x, y + h - 7, x + w, y + h - 7)
        self.text("NOTE", x + 2.5, y + h - 5.0, 2.8, title)
        for i, ln in enumerate(lines):
            self.text("TEXT_SMALL", x + 2.5, y + h - 12.0 - i * 5.0, 2.3, ln)
        return h

    # -- output -----------------------------------------------------------
    def save(self, path):
        out = []
        out += ["0", "SECTION", "2", "HEADER",
                "9", "$ACADVER", "1", "AC1009",
                "9", "$INSBASE", "10", "0.0", "20", "0.0", "30", "0.0",
                "9", "$EXTMIN", "10", "0.0", "20", "0.0", "30", "0.0",
                "9", "$EXTMAX", "10", "420.0", "20", "297.0", "30", "0.0",
                "9", "$LIMMIN", "10", "0.0", "20", "0.0",
                "9", "$LIMMAX", "10", "420.0", "20", "297.0",
                "9", "$LUNITS", "70", "2",
                "9", "$INSUNITS", "70", "4",
                "0", "ENDSEC"]

        out += ["0", "SECTION", "2", "TABLES",
                "0", "TABLE", "2", "LTYPE", "70", "1",
                "0", "LTYPE", "2", "CONTINUOUS", "70", "0",
                "3", "Solid line", "72", "65", "73", "0", "40", "0.0",
                "0", "ENDTAB",
                "0", "TABLE", "2", "LAYER", "70", str(len(LAYERS))]
        for name, col in LAYERS:
            out += ["0", "LAYER", "2", name, "70", "0",
                    "62", str(col), "6", "CONTINUOUS"]
        out += ["0", "ENDTAB",
                "0", "TABLE", "2", "STYLE", "70", "1",
                "0", "STYLE", "2", "STANDARD", "70", "0",
                "40", "0.0", "41", "1.0", "50", "0.0", "71", "0",
                "42", "2.5", "3", "txt", "4", "",
                "0", "ENDTAB",
                "0", "ENDSEC"]

        out += ["0", "SECTION", "2", "ENTITIES"] + self.e + ["0", "ENDSEC"]
        out += ["0", "EOF"]

        with open(path, "w", encoding="ascii", errors="replace") as f:
            f.write("\n".join(out) + "\n")


# ============================================================== SHEET 1
def sheet1(path):
    d = Dxf()
    d.border_and_title(1, "SHEET 1 : SYSTEM INTERCONNECTION")

    # ---- PC ------------------------------------------------------------
    d.block(22, 232, 74, 40, "INDUSTRIAL PC", "SEQApp + AXL library", "(AXM / AXC / AXD)")

    # ---- Ajinextek boards ---------------------------------------------
    d.block(22, 186, 74, 34, "AJINEXTEK  AXM", "Motion board, 1 axis", "pulse out (line driver)")
    d.block(22, 140, 74, 34, "AJINEXTEK  AXC", "SIO-HPC4L", "enc diff in / trig out")
    d.block(22, 100, 74, 30, "AJINEXTEK  AXD", "Digital I/O")

    # PCI/PCIe bus lines from PC down to boards
    for yy, yt in ((232, 220), (232, 174), (232, 130)):
        pass
    d.poly("WIRE_SIG", [(59, 232), (59, 226), (12.5, 226)])
    d.poly("WIRE_SIG", [(14, 226), (14, 203), (22, 203)])
    d.poly("WIRE_SIG", [(14, 226), (14, 157), (22, 157)])
    d.poly("WIRE_SIG", [(14, 226), (14, 115), (22, 115)])
    d.text("TEXT_SMALL", 16, 228, 2.3, "PCI / PCIe BUS")
    for yy in (203, 157, 115):
        d.dot("WIRE_SIG", 14, yy)

    # ---- Servo driver ---------------------------------------------------
    dx, dy, dw, dh = 165, 96, 96, 176
    d.block(dx, dy, dw, dh, "SERVO DRIVER", "PANASONIC  MBDLT25SM",
            "MINAS A6S  400W  200V")
    # connector stubs on driver
    d.text("TEXT_SMALL", dx + 3, dy + dh - 26, 2.6, "X4  (50P I/O)")
    d.line("COMPONENT", dx, dy + dh - 30, dx + 34, dy + dh - 30)
    d.text("TEXT_SMALL", dx + 3, dy + 34, 2.6, "X5  EXT SCALE")
    d.text("TEXT_SMALL", dx + 3, dy + 16, 2.6, "U / V / W")
    d.text("TEXT_SMALL", dx + 52, dy + 16, 2.6, "L1 L2 L3 / L1C L2C")

    # ---- Motor / scale / camera ----------------------------------------
    d.block(306, 236, 84, 36, "LINEAR MOTOR", "1 axis  (scan axis)")
    d.block(306, 186, 84, 36, "LINEAR SCALE", "full-closed feedback")
    d.block(306, 120, 84, 44, "LINE SCAN CAMERA", "Control I/O  6P",
            "pin1 TRIG IN / pin3 GND")

    # ---- Power ----------------------------------------------------------
    d.block(22, 58, 74, 30, "AC 200-240V", "1PH / 3PH  + PE")
    d.block(120, 58, 66, 30, "DC 24V PSU", "I/O power")

    # ================= wiring =====================
    # AC -> driver
    d.poly("WIRE_PWR", [(96, 73), (140, 73), (140, 112), (165, 112)])
    d.arrow("WIRE_PWR", 165, 112, 1, 0)
    d.text("TEXT_SMALL", 100, 75.5, 2.4, "AC200-240V + PE")

    # driver U/V/W -> motor
    d.poly("WIRE_PWR", [(261, 112), (285, 112), (285, 254), (306, 254)])
    d.arrow("WIRE_PWR", 306, 254, 1, 0)
    d.text("TEXT_SMALL", 264, 114.5, 2.4, "U V W + PE")

    # scale -> driver X5
    d.poly("WIRE_DIFF", [(306, 204), (276, 204), (276, 130), (261, 130)])
    d.arrow("WIRE_DIFF", 261, 130, -1, 0)
    d.text("TEXT_SMALL", 278, 168, 2.4, "SCALE FB")
    d.text("TEXT_SMALL", 278, 163, 2.4, "-> X5")

    # AXM -> X4 command/status
    d.poly("WIRE_SIG", [(96, 203), (130, 203), (130, 246), (165, 246)])
    d.arrow("WIRE_SIG", 165, 246, 1, 0)
    d.text("TEXT_SMALL", 99, 205.5, 2.4, "PULS+/- SIGN+/-  SRV-ON  A-CLR  CL")
    d.text("TEXT_SMALL", 99, 200.5, 2.4, "ALM  S-RDY  INP        -> SHEET 2")

    # driver X4 pulse regen -> AXC HPC4L
    d.poly("WIRE_DIFF", [(165, 236), (146, 236), (146, 157), (96, 157)])
    d.arrow("WIRE_DIFF", 96, 157, -1, 0)
    d.text("TEXT_SMALL", 100, 165, 2.4, "OA+/- OB+/- OZ+/-")
    d.text("TEXT_SMALL", 100, 160, 2.4, "PULSE REGEN   -> SHEET 3")

    # AXC -> camera trigger
    d.poly("WIRE_TRIG", [(96, 148), (112, 148), (112, 92), (296, 92), (296, 142), (306, 142)])
    d.arrow("WIRE_TRIG", 306, 142, 1, 0)
    d.text("TEXT_SMALL", 150, 94.5, 2.4, "TRIG OUT 0   5V TTL push-pull   -> SHEET 3")

    # 24V -> driver X4 COM, and to DIO
    d.poly("WIRE_PWR", [(186, 73), (204, 73), (204, 226), (165, 226)])
    d.arrow("WIRE_PWR", 165, 226, -1, 0)
    d.text("TEXT_SMALL", 206, 150, 2.4, "DC24V")
    d.text("TEXT_SMALL", 206, 145, 2.4, "COM+/COM-")
    d.poly("WIRE_PWR", [(153, 73), (153, 115), (96, 115)])
    d.arrow("WIRE_PWR", 96, 115, -1, 0)
    d.dot("WIRE_PWR", 153, 73)

    # DIO -> limits / EMG
    d.poly("WIRE_SIG", [(96, 107), (232, 107), (232, 96)])
    d.arrow("WIRE_SIG", 232, 96, 0, -1)
    d.text("TEXT_SMALL", 100, 109.5, 2.4, "LIMIT + / -  , HOME , EMG")

    # ---- legend ---------------------------------------------------------
    lx, ly = 250, 62
    d.rect("NOTE", lx, ly, 158, 40)
    d.line("NOTE", lx, ly + 33, lx + 158, ly + 33)
    d.text("NOTE", lx + 2.5, ly + 35.0, 2.8, "LEGEND")
    items = [("WIRE_PWR",  "POWER  (AC / DC)"),
             ("WIRE_SIG",  "SIGNAL (single ended)"),
             ("WIRE_DIFF", "DIFFERENTIAL PAIR (shielded TP)"),
             ("WIRE_TRIG", "TRIGGER 5V TTL")]
    for i, (lay, txt) in enumerate(items):
        yy = ly + 27 - i * 6.5
        d.line(lay, lx + 4, yy, lx + 22, yy)
        d.text("TEXT_SMALL", lx + 26, yy, 2.4, txt, 0, 2)

    # ---- notes ----------------------------------------------------------
    d.note_box(120, 96, 126, [
        "1. FASTECH Ez-ML-PE-PAN REMOVED. X4 WIRED DIRECT TO AJINEXTEK.",
        "2. TRIGGER IS DERIVED FROM PULSE REGEN (ACTUAL POSITION),",
        "   NEVER FROM THE COMMAND PULSE TRAIN.",
        "3. P_cmd = 0.5 um/pulse   UPP = 0.1 um/count   PITCH = 5.0 um",
        "4. PIN NUMBERS TBD - VERIFY AGAINST DRIVER / CAMERA MANUAL.",
        "5. LINEAR MOTOR MAGNETIC POLE DETECTION SEQUENCE MUST BE",
        "   CONFIRMED BEFORE REMOVING THE Ez-ML MODULE.",
    ])
    d.save(path)


# ============================================================== SHEET 2
def sheet2(path):
    d = Dxf()
    d.border_and_title(2, "SHEET 2 : X4 COMMAND / STATUS WIRING")

    # left rail : Ajinextek
    d.block(24, 96, 86, 176, "AJINEXTEK", "AXM motion board", "+ AXD digital I/O")
    # right rail : driver X4
    d.block(292, 96, 86, 176, "MBDLT25SM", "CONNECTOR  X4", "50 PIN")

    rows = [
        # (label_left,      label_right,      layer,      dir)   dir: 1 L->R, -1 R->L
        ("PULSE OUT +",     "PULS1",          "WIRE_DIFF",  1),
        ("PULSE OUT -",     "PULS2",          "WIRE_DIFF",  1),
        ("DIR OUT +",       "SIGN1",          "WIRE_DIFF",  1),
        ("DIR OUT -",       "SIGN2",          "WIRE_DIFF",  1),
        ("SERVO ON",        "SRV-ON",         "WIRE_SIG",   1),
        ("ALARM CLEAR",     "A-CLR",          "WIRE_SIG",   1),
        ("DEV CTR CLEAR",   "CL",             "WIRE_SIG",   1),
        ("OVERTRAVEL +",    "POT",            "WIRE_SIG",   1),
        ("OVERTRAVEL -",    "NOT",            "WIRE_SIG",   1),
        ("ALARM IN",        "ALM+ / ALM-",    "WIRE_SIG",  -1),
        ("SERVO READY IN",  "S-RDY+ / -",     "WIRE_SIG",  -1),
        ("IN-POSITION IN",  "INP+ / INP-",    "WIRE_SIG",  -1),
        ("BRAKE OUT",       "BRK-OFF+ / -",   "WIRE_SIG",  -1),
        ("DC24V +",         "COM+",           "WIRE_PWR",   1),
        ("DC24V 0V",        "COM-",           "WIRE_PWR",   1),
    ]

    y0, dy = 258.0, 10.5
    for i, (ll, rl, lay, dr) in enumerate(rows):
        y = y0 - i * dy
        d.term(110, y, ll, "l")
        d.term(292, y, rl, "r")
        d.line(lay, 110, y, 292, y)
        if dr > 0:
            d.arrow(lay, 288, y, 1, 0)
        else:
            d.arrow(lay, 114, y, -1, 0)
        # pin number placeholder
        d.rect("DIM", 258, y - 3.2, 26, 6.4)
        d.text("TEXT_SMALL", 271, y, 2.3, "X4-__", 1, 2)

    d.text("TEXT", 201, 268, 3.0, "SIGNAL", 1, 2)
    d.text("TEXT_SMALL", 271, 268, 2.4, "PIN (TBD)", 1, 2)

    d.note_box(24, 20, 354, [
        "1. PIN NUMBER COLUMN IS INTENTIONALLY LEFT BLANK. THE X4 PIN ASSIGNMENT WAS NOT VERIFIED AGAINST THE",
        "   MBDLT25SM MANUAL. FILL IN FROM THE OFFICIAL PIN LAYOUT BEFORE HARNESS FABRICATION.",
        "2. COMMAND PULSE : USE LINE DRIVER (DIFFERENTIAL) OUTPUT. SET AxmMotSetPulseOutMethod TO 1-PULSE MODE",
        "   (PULSE + DIR, uMethod 0..3) AND MATCH DRIVER Pr0.05..Pr0.07.",
        "3. ELECTRONIC GEAR (Pr0.08..Pr0.10) SET SO THAT ONE COMMAND PULSE = 0.5 um OF TRAVEL.",
        "   AT 500 mm/s THIS GIVES 1.0 Mpps, WELL INSIDE THE 4 Mpps DRIVER COMMAND INPUT LIMIT.",
        "4. STATUS OUTPUTS (ALM / S-RDY / INP / BRK-OFF) ARE OPTO-ISOLATED PAIRS - OBSERVE POLARITY.",
        "5. HARNESS : 50 PIN CRIMP CONNECTOR. SHIELDED TWISTED PAIR FOR PULS / SIGN PAIRS,",
        "   SHIELD GROUNDED AT THE DRIVER END ONLY. ROUTE CLEAR OF U/V/W MOTOR POWER.",
        "6. OVERTRAVEL / EMG MAY ALSO BE HARD-WIRED TO THE SAFETY CIRCUIT - SEE MACHINE SAFETY DRAWING.",
    ])
    d.save(path)


# ============================================================== SHEET 3
def sheet3(path):
    d = Dxf()
    d.border_and_title(3, "SHEET 3 : TRIGGER CHAIN  (PULSE REGEN -> HPC4L -> CAMERA)")

    # --- driver X4 pulse regen block
    d.block(22, 178, 84, 82, "MBDLT25SM", "X4 PULSE REGEN", "line driver out")
    # --- HPC4L
    d.block(160, 150, 100, 110, "AJINEXTEK", "SIO-HPC4L", "4CH enc / trigger")
    # --- camera
    d.block(310, 178, 86, 82, "LINE SCAN CAMERA", "Control I/O 6P")

    # differential pairs driver -> HPC4L
    pairs = [("OA+", "ENC A+"), ("OA-", "ENC A-"),
             ("OB+", "ENC B+"), ("OB-", "ENC B-"),
             ("OZ+", "ENC Z+"), ("OZ-", "ENC Z-"),
             ("SG",  "GND")]
    y0, dy = 250.0, 9.5
    for i, (a, b) in enumerate(pairs):
        y = y0 - i * dy
        lay = "WIRE_DIFF" if i < 6 else "WIRE_SIG"
        d.term(106, y, a, "l")
        d.term(160, y, b, "r")
        d.line(lay, 106, y, 160, y)
        d.arrow(lay, 156, y, 1, 0)
    d.text("TEXT_SMALL", 133, 256, 2.4, "SHIELDED TP x3", 1, 2)

    # HPC4L trigger out -> camera
    yT = 236.0
    d.term(260, yT, "TRIG OUT 0", "r")
    # series resistor
    rx = 282.0
    d.line("WIRE_TRIG", 260, yT, rx, yT)
    d.rect("WIRE_TRIG", rx, yT - 3.0, 14, 6.0)
    d.text("TEXT_SMALL", rx + 7, yT + 6.5, 2.3, "33-47R", 1, 1)
    d.line("WIRE_TRIG", rx + 14, yT, 310, yT)
    d.arrow("WIRE_TRIG", 310, yT, 1, 0)
    d.term(310, yT, "pin1  TRIG IN", "r")

    yG = 224.0
    d.term(260, yG, "GND", "r")
    d.line("WIRE_SIG", 260, yG, 310, yG)
    d.term(310, yG, "pin3  DC GND", "r")

    # camera strobe back for verification
    yS = 206.0
    d.term(310, yS, "pin4  STROBE OUT", "r")
    d.poly("WIRE_SIG", [(310, yS), (296, yS), (296, 168), (206, 168)])
    d.arrow("WIRE_SIG", 206, 168, -1, 0)
    d.text("TEXT_SMALL", 210, 170.5, 2.4, "STROBE -> SCOPE / COUNTER (VERIFY V-4)")

    # camera TDI/scan direction input (optional)
    yD = 194.0
    d.term(310, yD, "pin2  DIRECTION IN", "r")
    d.poly("WIRE_SIG", [(310, yD), (302, yD), (302, 160), (260, 160)])
    d.arrow("WIRE_SIG", 260, 160, -1, 0)
    d.text("TEXT_SMALL", 264, 162.5, 2.4, "OPTIONAL (bi-dir scan)")

    # --- isolation option -------------------------------------------------
    ox, oy = 22, 96
    d.rect("NOTE", ox, oy, 160, 56)
    d.line("NOTE", ox, oy + 49, ox + 160, oy + 49)
    d.text("NOTE", ox + 2.5, oy + 51.0, 2.8, "OPTION : GALVANIC ISOLATION")
    d.text("TEXT_SMALL", ox + 4, oy + 42, 2.4, "USE ONLY IF GROUND POTENTIAL DIFFERENCE")
    d.text("TEXT_SMALL", ox + 4, oy + 37, 2.4, "CAUSES FALSE TRIGGERS.")
    # simple opto symbol
    sx, sy = ox + 16, oy + 12
    d.rect("COMPONENT", sx, sy, 44, 18)
    d.text("TEXT_SMALL", sx + 22, sy + 9, 2.4, "6N137", 1, 2)
    d.line("WIRE_TRIG", sx - 14, sy + 9, sx, sy + 9)
    d.line("WIRE_TRIG", sx + 44, sy + 9, sx + 58, sy + 9)
    d.arrow("WIRE_TRIG", sx + 58, sy + 9, 1, 0)
    d.text("TEXT_SMALL", sx - 14, sy + 12.5, 2.3, "HPC4L")
    d.text("TEXT_SMALL", sx + 46, sy + 12.5, 2.3, "CAMERA")
    d.text("TEXT_SMALL", ox + 4, oy + 4, 2.3, "HIGH SPEED OPTO ONLY (>=10 Mbps). STANDARD OPTO IS TOO SLOW.")

    # --- timing / parameter table ----------------------------------------
    tx, ty = 196, 96
    d.rect("NOTE", tx, ty, 182, 56)
    d.line("NOTE", tx, ty + 49, tx + 182, ty + 49)
    d.text("NOTE", tx + 2.5, ty + 51.0, 2.8, "TRIGGER PARAMETERS")
    rows = [
        "TRIGGER PITCH        5.0 um   (= pixel pitch / magnification)",
        "UPP  (1 count)       0.1 um   -> PITCH = 50 COUNTS  (integer, exact)",
        "ENC INPUT METHOD     A/B PHASE x4  (AxcSignalSetEncInputMethod 0x03)",
        "TRIGGER FUNCTION     PERIODIC MODE 0x03  (AxcTriggerSetFunction)",
        "PULSE WIDTH          2.0 us   (camera minimum 1 us)",
        "OUTPUT LEVEL         HIGH ACTIVE -> camera trigger = RISING EDGE",
        "MAX SPEED            v_max = camera line rate x 5.0 um",
    ]
    for i, r in enumerate(rows):
        d.text("TEXT_SMALL", tx + 4, ty + 42 - i * 5.6, 2.3, r)

    d.note_box(22, 20, 356, [
        "1. TRIGGER MUST COME FROM THE PULSE REGEN OUTPUT (ACTUAL POSITION). USING THE COMMAND PULSE TRAIN",
        "   IGNORES FOLLOWING ERROR AND SETTLING, AND DEFEATS THE PURPOSE OF POSITION SYNCHRONISED TRIGGERING.",
        "2. SET THE DRIVER PULSE REGEN SOURCE TO THE EXTERNAL SCALE, NOT THE MOTOR ENCODER.",
        "3. SIO-HPC4 HAS NO DISTANCE-PERIODIC TRIGGER MODE. USE AxcTriggerSetFunction(ch,0x03) PERIODIC MODE",
        "   WITH AxcTriggerSetBlock(ch, start, end, pitch). PATTERN MODE IS A FREQUENCY TIMER - DO NOT USE.",
        "4. PERIODIC MODE USES NO BUFFER : TRIGGER COUNT IS UNLIMITED (tens of thousands per scan is fine).",
        "5. SERIES RESISTOR 33-47R AT THE SOURCE IF CABLE EXCEEDS 1 m. RINGING THAT CROSSES THE INPUT",
        "   THRESHOLD WILL BE COUNTED AS EXTRA TRIGGERS.",
        "6. VERIFY : CLEAR TRIGGER COUNT, SCAN 200 mm, READ COUNT. EXPECT 40000 (= 200 mm / 5 um).",
    ])
    d.save(path)


# ==============================================================
if __name__ == "__main__":
    import os, sys
    outdir = sys.argv[1]
    os.makedirs(outdir, exist_ok=True)
    sheet1(os.path.join(outdir, "LineScan_Trigger_SH1_System.dxf"))
    sheet2(os.path.join(outdir, "LineScan_Trigger_SH2_X4_Wiring.dxf"))
    sheet3(os.path.join(outdir, "LineScan_Trigger_SH3_Trigger_Chain.dxf"))
    for f in sorted(os.listdir(outdir)):
        p = os.path.join(outdir, f)
        print(f"{f:44s} {os.path.getsize(p):>8,} bytes")
