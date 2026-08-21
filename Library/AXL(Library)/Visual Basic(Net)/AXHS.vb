Option Strict Off
Option Explicit On
Module AXHS
    '****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ---------
    '**
    '** AXHS.BAS
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Resource Define Header File
    '**
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Source Change Indices
    '** ---------------------
    '**
    '** (None)
    '**
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Website
    '** ---------------------
    '**
    '** http://www.ajinextek.com
    '**
    '*****************************************************************************
    '*****************************************************************************
    '*
    
    ' Define Structure DCB
    Public Structure DCB
        Public DCBlength As Integer
        Public BaudRate As Integer
        Public fBitFields As Integer
        Public wReserved As Integer
        Public XonLim As Integer
        Public XoffLim As Integer
        Public ByteSize As Byte
        Public Parity As Byte
        Public StopBits As Byte
        Public XonChar As Byte
        Public XoffChar As Byte
        Public ErrorChar As Byte
        Public EofChar As Byte
        Public EvtChar As Byte
        Public wReserved1 As Integer
    End Structure

    Public Const F_BINARY = 1
    Public Const F_PARITY = 2
    Public Const F_OUTX_CTS_FLOW = 4
    Public Const F_OUTX_DSR_FLOW = 8

    'DTR Control Flow Values.
    Public Const F_DTR_CONTROL_ENABLE = &H10
    Public Const F_DTR_CONTROL_HANDSHAKE = &H20

    Public Const F_DSR_SENSITIVITY = &H40
    Public Const F_TX_CONTINUE_ON_XOFF = &H80
    Public Const F_OUT_X = &H100
    Public Const F_IN_X = &H200
    Public Const F_ERROR_CHAR = &H400
    Public Const F_NULL = &H800

    'RTS Control Flow Values
    Public Const F_RTS_CONTROL_ENABLE = &H1000
    Public Const F_RTS_CONTROL_HANDSHAKE = &H2000
    Public Const F_RTS_CONTROL_TOGGLE = &H3000

    Public Const F_ABORT_ON_ERROR = &H4000

    '---------Parity flags--------
    Public Const EVENPARITY = 2
    Public Const MARKPARITY = 3
    Public Const NOPARITY = 0
    Public Const ODDPARITY = 1
    Public Const SPACEPARITY = 4

    '---------StopBits-----------
    Public Const ONESTOPBIT = 0
    Public Const ONE5STOPBITS = 1
    Public Const TWOSTOPBITS = 2

    ' Define Structure COMMTIMEOUTS
    Public Structure COMMTIMEOUTS
        Public ReadIntervalTimeout As Int32
        Public ReadTotalTimeoutMultiplier As Int32
        Public ReadTotalTimeoutConstant As Int32
        Public WriteTotalTimeoutMultiplier As Int32
        Public WriteTotalTimeoutConstant As Int32
    End Structure
    '-----------------------------------------------------------------------------------------------

    'Constants for the dwDesiredAccess parameter of the CreateFile() function
    Public Const GENERIC_READ = &H80000000
    Public Const GENERIC_WRITE = &H40000000

    'Constants for the dwShareMode parameter of the CreateFile() function
    Public Const FILE_SHARE_READ = &H1
    Public Const FILE_SHARE_WRITE = &H2

    'Constants for the dwCreationDisposition parameter of the CreateFile() function
    Public Const CREATE_NEW = 1
    Public Const CREATE_ALWAYS = 2
    Public Const OPEN_EXISTING = 3

    'Constants for the dwFlagsAndAttributes parameter of the CreateFile() function
    Public Const FILE_ATTRIBUTE_NORMAL = &H80
    Public Const FILE_FLAG_OVERLAPPED = &H40000000

    '-----------------------------------------------------------------------------------------------
    'Error codes reported by the CreateFile().
    'More error codes with descriptions are available at MSDN
    Public Const ERROR_FILE_NOT_FOUND = 2
    Public Const ERROR_ACCESS_DENIED = 5
    Public Const ERROR_INVALID_HANDLE = 6

    ' Define Structure COMSTAT
    Public Structure COMSTAT
        Public Const fCtsHold As UInteger = &H1
        Public Const fDsrHold As UInteger = &H2
        Public Const fRlsdHold As UInteger = &H4
        Public Const fXoffHold As UInteger = &H8
        Public Const fXoffSent As UInteger = &H10
        Public Const fEof As UInteger = &H20
        Public Const fTxim As UInteger = &H40
        Public fBitFields As Int32
        Public cbInQue As Int32
        Public cbOutQue As Int32

    End Structure

    ' Define Structure OVERLAPPED
    Public Structure OVERLAPPED
        Public Internal As Integer
        Public InternalHigh As Integer
        Public offset As Integer
        Public offsetHigh As Integer
        Public hEvent As Integer
    End Structure
    ' Define Baseboard  
    Public Const AXT_UNKNOWN As Short = &H0S                                   ' Unknown Baseboard                                                      
    Public Const AXT_BIHR As Short = &H1S                                      ' ISA bus, Half size                                                     
    Public Const AXT_BIFR As Short = &H2S                                      ' ISA bus, Full size                                                     
    Public Const AXT_BPHR As Short = &H3S                                      ' PCI bus, Half size                                                     
    Public Const AXT_BPFR As Short = &H4S                                      ' PCI bus, Full size                                                     
    Public Const AXT_BV3R As Short = &H5S                                      ' VME bus, 3U size                                                       
    Public Const AXT_BV6R As Short = &H6S                                      ' VME bus, 6U size                                                       
    Public Const AXT_BC3R As Short = &H7S                                      ' cPCI bus, 3U size                                                      
    Public Const AXT_BC6R As Short = &H8S                                      ' cPCI bus, 6U size                                                      
    Public Const AXT_BEHR As Short = &H9S                                      ' PCIe bus, Half size
    Public Const AXT_BEFR As Short = &HAS                                      ' PCIe bus, Full size
    Public Const AXT_BEHD As Short = &HBS                                      ' PCIe bus, Half size, DB-32T
    Public Const AXT_FMNSH4D As Short = &H52S                                  ' ISA bus, Full size, DB-32T, SIO-2V03 * 2                               
    Public Const AXT_PCI_DI64R As Short = &H43S                                ' PCI bus, Digital IN 64 point
    Public Const AXT_PCIE_DI64R As Short = &H44S                               ' PCIe bus, Digital IN 64 point
    Public Const AXT_PCI_DO64R As Short = &H53S                                ' PCI bus, Digital OUT 64 point
    Public Const AXT_PCIE_DO64R As Short = &H54S                               ' PCIe bus, Digital OUT 64 point
    Public Const AXT_PCI_DB64R As Short = &H63S                                ' PCI bus, Digital IN 32 point, OUT 32 point
    Public Const AXT_PCIE_DB64R As Short = &H64S                               ' PCIe bus, Digital IN 32 point, OUT 32 point
    Public Const AXT_BPFR_COM As Short = &H70S                                 ' PCI bus, Full size, For serial function modules.
    Public Const AXT_PCIN204 As Short = &H82S                                  ' PCI bus, Half size On-Board 2 Axis controller.
    Public Const AXT_BPHD As Short = &H83S                                     ' PCI bus, Half size, DB-32T                                             
    Public Const AXT_PCIN404 As Short = &H84S                                  ' PCI bus, Half size On-Board 4 Axis controller.                         
    Public Const AXT_PCIN804 As Short = &H85S                                  ' PCI bus, Half size On-Board 8 Axis controller.                         
    Public Const AXT_PCIEN804 As Short = &H86S                                 ' PCIe bus, Half size On-Board 8 Axis controller.
    Public Const AXT_PCIEN404 As Short = &H87S                                 ' PCIe bus, Half size On-Board 4 Axis controller.
    Public Const AXT_PCI_AIO1602HR As Short = &H93S                            ' PCI bus, Half size, AI-16ch, AO-2ch AI16HR                             
    Public Const AXT_PCI_R1604 As Short = &HC1S                                ' PCI bus[PCI9030], Half size, RTEX based 16 axis controller             
    Public Const AXT_PCI_R3204 As Short = &HC2S                                ' PCI bus[PCI9030], Half size, RTEX based 32 axis controller             
    Public Const AXT_PCI_R32IO As Short = &HC3S                                ' PCI bus[PCI9030], Half size, RTEX based IO only.
    Public Const AXT_PCI_REV2 As Short = &HC4S                                 ' Reserved.                                                              
    Public Const AXT_PCI_R1604MLII As Short = &HC5S                            ' PCI bus[PCI9030], Half size, Mechatrolink-II 16/32 axis controller.    
    Public Const AXT_PCI_R0804MLII As Short = &HC6S                            ' PCI bus[PCI9030], Half size, Mechatrolink-II 08 axis controller.
    Public Const AXT_PCI_Rxx00MLIII As Short = &HC7S                           ' Master PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 Slave module support
    Public Const AXT_PCIE_Rxx00MLIII As Short = &HC8S                          ' Master PCI Express Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    Public Const AXT_PCP2_Rxx00MLIII As Short = &HC9S                          ' Master PCI/104-Plus Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    Public Const AXT_PCI_R1604SIIIH As Short = &HCAS                           ' PCI bus[PCI9030], Half size, SSCNET III / H 16/32 axis controller.  
    Public Const AXT_PCI_R32IOEV As Short = &HCBS                              ' PCI bus[PCI9030], Half size, RTEX based IO only. Economic version.
    Public Const AXT_PCIE_R0804RTEX As Short = &HCCS                           ' PCIe bus, Half size, Half size, RTEX based 08 axis controller.
    Public Const AXT_PCIE_R1604RTEX As Short = &HCDS                           ' PCIe bus, Half size, Half size, RTEX based 16 axis controller.
    Public Const AXT_PCIE_R2404RTEX As Short = &HCES                           ' PCIe bus, Half size, Half size, RTEX based 24 axis controller.
    Public Const AXT_PCIE_R3204RTEX As Short = &HCFS                           ' PCIe bus, Half size, Half size, RTEX based 32 axis controller.
    Public Const AXT_PCIE_Rxx04SIIIH As Short = &HD0S                          ' PCIe bus, Half size, SSCNET III / H 16(or 32)-axis(CAMC-QI based) controller.
    Public Const AXT_PCIE_Rxx00SIIIH As Short = &HD1S                          ' PCIe bus, Half size, SSCNET III / H Max. 32-axis(DSP Based) controller.
    Public Const AXT_ETHERCAT_RTOSV5 As Short = &HD2S                          ' EtherCAT, RTOS(On Time), Version 5.29
    Public Const AXT_PCI_Nx04_A As Short = &HD3S                               ' PCI bus, Half size On-Board x Axis controller For Rtos.
    Public Const AXT_PCI_R3200MLIII_IO As Short = &HD4S                        ' PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 IO only	controller
    Public Const AXT_PCIE_Rxx05MLIII As Short = &HD5S                          ' PCIe bus, Half size, Mechatrolink III 32 axis(DSP Based) controller.
    Public Const AXT_PCIE_Rxx05SIIIH As Short = &HD6S                          ' PCIe bus, Half size, Sscnet III / H  32 axis(DSP Based) controller.
    Public Const AXT_PCIE_Rxx05RTEX As Short = &HD7S                           ' PCIe bus, Half size, RTEX 32 axis(DSP Based) controller.

    ' Define Module                                                     
    'Public Const AXT_UNKNOWN As Short = &H0S                                  ' Unknown Baseboard
    Public Const AXT_SMC_2V01 As Short = &H1S                                  ' CAMC-5M, 2 Axis
    Public Const AXT_SMC_2V02 As Short = &H2S                                  ' CAMC-FS, 2 Axis
    Public Const AXT_SMC_1V01 As Short = &H3S                                  ' CAMC-5M, 1 Axis
    Public Const AXT_SMC_1V02 As Short = &H4S                                  ' CAMC-FS, 1 Axis
    Public Const AXT_SMC_2V03 As Short = &H5S                                  ' CAMC-IP, 2 Axis
    Public Const AXT_SMC_4V04 As Short = &H6S                                  ' CAMC-QI, 4 Axis
    Public Const AXT_SMC_R1V04A4 As Short = &H7S                               ' CAMC-QI, 1 Axis, For RTEX A4 slave only
    Public Const AXT_SMC_1V03 As Short = &H8S                                  ' CAMC-IP, 1 Axis
    Public Const AXT_SMC_R1V04 As Short = &H9S                                 ' CAMC-QI, 1 Axis, For RTEX SLAVE only
    Public Const AXT_SMC_R1V04MLIISV As Short = &HAS                           ' CAMC-QI, 1 Axis, For Sigma-X series.
    Public Const AXT_SMC_R1V04MLIIPM As Short = &HBS                           ' 2 Axis, For Pulse output series(JEPMC-PL2910).
    Public Const AXT_SMC_2V04 As Short = &HCS                                  ' CAMC-QI, 2 Axis
    Public Const AXT_SMC_R1V04A5 As Short = &HDS                               ' CAMC-QI, 1 Axis, For RTEX A5N slave only
    Public Const AXT_SMC_R1V04MLIICL As Short = &HES                           ' CAMC-QI, 1 Axis, For Convex Linear Servo Drive   
    Public Const AXT_SMC_R1V04MLIICR As Short = &HFS                           ' CAMC-QI, 1 Axis, For Convex Rotary Servo Drive

    Public Const AXT_SMC_R1V04PM2Q As Short = &H10S                            ' CAMC-QI, 2 Axis, For RTEX SLAVE only(Pulse Output Module)
    Public Const AXT_SMC_R1V04PM2QE As Short = &H11S                           ' CAMC-QI, 4 Axis, For RTEX SLAVE only(Pulse Output Module)
    Public Const AXT_SMC_R1V04MLIIORI As Short = &H12S                         ' CAMC-QI, 1 Axis, For MLII Oriental Step Driver only
    Public Const AXT_SMC_R1V04A6 As Short = &H13S                              ' CAMC-QI, 1 Axis, For RTEX A5N slave only
    Public Const AXT_SMC_R1V04SIIIHMIV As Short = &H14S                        ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    Public Const AXT_SMC_R1V04SIIIHMIV_R As Short = &H15S                      ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    Public Const AXT_SMC_R1V04SIIIHME As Short = &H16S                         ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJE
    Public Const AXT_SMC_R1V04SIIIHME_R As Short = &H17S                       ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJE
    Public Const AXT_SMC_R1V04MLIIS7 As Short = &H1DS                          ' CAMC-QI, 1 Axis, For ML-II/YASKWA Sigma7(SGD7S)
    Public Const AXT_SMC_R1V04MLIIISV As Short = &H20S                         ' DSP, 1 Axis, For ML-3 SigmaV/YASKAWA only 
    Public Const AXT_SMC_R1V04MLIIIPM As Short = &H21S                         ' DSP, 1 Axis, For ML-3 SLAVE/AJINEXTEK only(Pulse Output Module)
    Public Const AXT_SMC_R1V04MLIIISV_MD As Short = &H22S                      ' DSP, 1 Axis, For ML-3 SigmaV-MD/YASKAWA only (Multi-Axis Control amp)
    Public Const AXT_SMC_R1V04MLIIIS7S As Short = &H23S                        ' DSP, 1 Axis, For ML-3 Sigma7S/YASKAWA only
    Public Const AXT_SMC_R1V04MLIIIS7W As Short = &H24S                        ' DSP, 2 Axis, For ML-3 Sigma7W/YASKAWA only(Dual-Axis control amp)
    Public Const AXT_SMC_R1V04MLIIIRS2 As Short = &H25S                        ' DSP, 1 Axis, For ML-3 RS2A/SANYO DENKY
    Public Const AXT_SMC_R1V04MLIIIS7_MD As Short = &H26S                      ' DSP, 1 Axis, For ML-3 Sigma7-MD/YASKAWA only (Multi-Axis Control amp)
    Public Const AXT_SMC_R1V04PM2QSIIIH As Short = &H60S                       ' CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    Public Const AXT_SMC_R1V04PM4QSIIIH As Short = &H61S                       ' CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    Public Const AXT_SIO_RCNT2SIIIH As Short = &H62S                           ' Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only
    Public Const AXT_SIO_RDI32SIIIH As Short = &H63S                           ' DI slave module, SSCNETIII AXT, IN 32-Channel
    Public Const AXT_SIO_RDO32SIIIH As Short = &H64S                           ' DO slave module, SSCNETIII AXT, OUT 32-Channel
    Public Const AXT_SIO_RDB32SIIIH As Short = &H65S                           ' DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel
    Public Const AXT_SIO_RAI16SIIIH As Short = &H66S                           ' AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit
    Public Const AXT_SIO_RAO08SIIIH As Short = &H67S                           ' A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit
    Public Const AXT_SMC_R1V04PM2QSIIIH_R As Short = &H68S                     ' AMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
    Public Const AXT_SMC_R1V04PM4QSIIIH_R As Short = &H69S                     ' CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
    Public Const AXT_SIO_RCNT2SIIIH_R As Short = &H6AS                         ' Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only 
    Public Const AXT_SIO_RDI32SIIIH_R As Short = &H6BS                         ' DI slave module, SSCNETIII AXT, IN 32-Channel 
    Public Const AXT_SIO_RDO32SIIIH_R As Short = &H6CS                         ' DO slave module, SSCNETIII AXT, OUT 32-Channel 
    Public Const AXT_SIO_RDB32SIIIH_R As Short = &H6DS                         ' DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel 
    Public Const AXT_SIO_RAI16SIIIH_R As Short = &H6ES                         ' AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit 
    Public Const AXT_SIO_RAO08SIIIH_R As Short = &H6FS                         ' A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit 
    Public Const AXT_SIO_RDI32MLIII As Short = &H70S                           ' DI slave module, MechatroLink III AXT, IN 32-Channel NPN
    Public Const AXT_SIO_RDO32MLIII As Short = &H71S                           ' DO slave module, MechatroLink III AXT, OUT 32-Channel  NPN
    Public Const AXT_SIO_RDB32MLIII As Short = &H72S                           ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  NPN
    Public Const AXT_SIO_RDI32MSMLIII As Short = &H73S                         ' DI slave module, MechatroLink III M-SYSTEM, IN 32-Channel
    Public Const AXT_SIO_RDO32AMSMLIII As Short = &H74S                        ' DO slave module, MechatroLink III M-SYSTEM, OUT 32-Channel
    Public Const AXT_SIO_RDI32PMLIII As Short = &H75S                          ' DI slave module, MechatroLink III AXT, IN 32-Channel PNP
    Public Const AXT_SIO_RDO32PMLIII As Short = &H76S                          ' DO slave module, MechatroLink III AXT, OUT 32-Channel  PNP
    Public Const AXT_SIO_RDB32PMLIII As Short = &H77S                          ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  PNP
    Public Const AXT_SIO_RDI16MLIII As Short = &H78S                           ' DI slave module, MechatroLink III M-SYSTEM, IN 16-Channel
    Public Const AXT_SIO_UNDEFINEMLIII As Short = &H79S                        ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    Public Const AXT_SIO_RDI32MLIIISFA As Short = &H7AS                        ' DI slave module, MechatroLink III AXT(SFA), IN 32-Channel NPN
    Public Const AXT_SIO_RDO32MLIIISFA As Short = &H7BS                        ' DO slave module, MechatroLink III AXT(SFA), OUT 32-Channel  NPN
    Public Const AXT_SIO_RDB32MLIIISFA As Short = &H7CS                        ' DB slave module, MechatroLink III AXT(SFA), IN 16-Channel, OUT 16-Channel  NPN
    Public Const AXT_SIO_RDB128MLIIIAI As short = &H7DS                        ' Intelligent I/O (Product by IAI), For MLII only
    Public Const AXT_SIO_RSIMPLEIOMLII As Short = &H7ES                        ' Digital IN/Out xxch, Simple I/O sereies, MLII only.
    Public Const AXT_SIO_RDO16AMLIII As Short = &H7FS                          ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
    Public Const AXT_SIO_RDI16MLII As Short = &H80S                            ' DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RDO16AMLII As Short = &H81S                           ' NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RDO16BMLII As Short = &H82S                           ' PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only  
    Public Const AXT_SIO_RDB96MLII As Short = &H83S                            ' Digital IN/OUT(Selectable), MAX 96 points, For MLII only
    Public Const AXT_SIO_RDO32RTEX As Short = &H84S                            ' Digital OUT    32ch
    Public Const AXT_SIO_RDI32RTEX As Short = &H85S                            ' Digital IN     32ch
    Public Const AXT_SIO_RDB32RTEX As Short = &H86S                            ' Digital IN/OUT 32ch
    Public Const AXT_SIO_RDO32RTEXNT1_D1 As Short = &H87S                      ' Digital OUT    32ch IntekPlus only
    Public Const AXT_SIO_RDI32RTEXNT1_D1 As Short = &H88S                      ' Digital IN     32ch IntekPlus only
    Public Const AXT_SIO_RDB32RTEXNT1_D1 As Short = &H89S                      ' Digital IN/OUT 32ch IntekPlus only
    Public Const AXT_SIO_RDO16BMLIII As Short = &H8AS                          ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
    Public Const AXT_SIO_RDB32ML2NT1 As Short = &H8BS                          ' DB slave module, MechatroLink2 AJINEXTEK NT1 Series
    Public Const AXT_SIO_RDB128YSMLIII As Short = &H8CS                        ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    Public Const AXT_SIO_DI32_P As Short = &H92S                               ' Digital IN  32ch, PNP type(source type)
    Public Const AXT_SIO_DO32T_P As Short = &H93S                              ' Digital OUT 32ch, Power TR, PNT type(source type)
    Public Const AXT_SIO_RDB128MLII As Short = &H94S                           ' Digital IN  64ch / OUT 64ch, MLII Only(JEPMC-IO2310)
    Public Const AXT_SIO_RDI32 As Short = &H95S                                ' Digital IN  32ch, For RTEX only
    Public Const AXT_SIO_RDO32 As Short = &H96S                                ' Digital OUT 32ch, For RTEX only
    Public Const AXT_SIO_DI32 As Short = &H97S                                 ' Digital IN  32ch
    Public Const AXT_SIO_DO32P As Short = &H98S                                ' Digital OUT 32ch
    Public Const AXT_SIO_DB32P As Short = &H99S                                ' Digital IN  16ch / OUT 16ch
    Public Const AXT_SIO_RDB32T As Short = &H9AS                               ' Digital IN  16ch / OUT 16ch, For RTEX only
    Public Const AXT_SIO_DO32T As Short = &H9ES                                ' Digital OUT 16ch, Power TR Output
    Public Const AXT_SIO_DB32T As Short = &H9FS                                ' Digital IN  16ch / OUT 16ch, Power TR Output
    Public Const AXT_SIO_RAI16RB As Short = &HA0S                              ' A0h(160) : AI 16Ch, 16 bit, For RTEX only
    Public Const AXT_SIO_AI4RB As Short = &HA1S                                ' A1h(161) : AI 4Ch, 12 bit
    Public Const AXT_SIO_AO4RB As Short = &HA2S                                ' A2h(162) : AO 4Ch, 12 bit
    Public Const AXT_SIO_AI16H As Short = &HA3S                                ' A3h(163) : AI 4Ch, 16 bit
    Public Const AXT_SIO_AO8H As Short = &HA4S                                 ' A4h(164) : AO 4Ch, 16 bit
    Public Const AXT_SIO_AI16HB As Short = &HA5S                               ' A5h(165) : AI 16Ch, 16 bit (SIO-AI16HR(input module))
    Public Const AXT_SIO_AO2HB As Short = &HA6S                                ' A6h(166) : AO 2Ch, 16 bit  (SIO-AI16HR(output module))
    Public Const AXT_SIO_RAI8RB As Short = &HA7S                               ' A7h(167) : AI 8Ch, 16 bit, For RTEX only
    Public Const AXT_SIO_RAO4RB As Short = &HA8S                               ' A8h(168) : AO 4Ch, 16 bit, For RTEX only
    Public Const AXT_SIO_RAI4MLII As Short = &HA9S                             ' A9h(169) : AI 4Ch, 16 bit, For MLII only

    Public Const AXT_SIO_RAO2MLII As Short = &HAAS                             ' AAh(170) : AO 2Ch, 16 bit, For MLII only
    Public Const AXT_SIO_RAVCI4MLII As Short = &HABS                           ' DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RAVO2MLII As Short = &HACS                            ' DC VOLTAGE OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RACO2MLII As Short = &HADS                            ' DC CURRENT OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RATI4MLII As Short = &HAES                            ' THERMOCOUPLE INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RARTDI4MLII As Short = &HAFS                          ' RTD INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RCNT2MLII As Short = &HB0S                            ' Counter slave Module, Reversible counter, 2 channels (Product by YASKAWA)
    Public Const AXT_SIO_CN2CH As Short = &HB1S                                ' Counter Module, 2 channels, Remapped ID, Actual ID is (0xA8)
    Public Const AXT_SIO_RCNT2RTEX As Short = &HB2S                            ' Counter slave module, Reversible counter, 2 channels, For RTEX Only
    Public Const AXT_SIO_RCNT2MLIII As Short = &HB3S                           ' Counter slave moudle, MechatroLink III AXT, 2 ch, Trigger per channel
    Public Const AXT_SIO_RHPC4MLIII As Short = &HB4S                           ' Counter slave moudle, MechatroLink III AXT, 4 ch
    Public Const AXT_SIO_RAI16RTEX As Short = &HC0S                            ' ANALOG VOLTAGE INPUT(+- 10V) 16 Channel RTEX 
    Public Const AXT_SIO_RAO08RTEX As Short = &HC1S                            ' ANALOG VOLTAGE OUTPUT(+- 10V) 08 Channel RTEX
    Public Const AXT_SIO_RAI8MLIII As Short = &HC2S                            ' AI slave module, MechatroLink III AXT, Analog IN 8ch, 16 bit
    Public Const AXT_SIO_RAI16MLIII As Short = &HC3S                           ' AI slave module, MechatroLink III AXT, Analog IN 16ch, 16 bit
    Public Const AXT_SIO_RAO4MLIII As Short = &HC4S                            ' A0 slave module, MechatroLink III AXT, Analog OUT 4ch, 16 bit
    Public Const AXT_SIO_RAO8MLIII As Short = &HC5S                            ' A0 slave module, MechatroLink III AXT, Analog OUT 8ch, 16 bit
    Public Const AXT_SIO_RAVO4MLII As Short = &HC6S                            ' DC VOLTAGE OUTPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_SIO_RAV04MLIII As Short = &HC7S                           ' AO Slave module, MechatroLink III M-SYSTEM Voltage output module
    Public Const AXT_SIO_RAVI4MLIII As Short = &HC8S                           ' AI Slave module, MechatroLink III M-SYSTEM Voltage/Current input module
    Public Const AXT_SIO_RAI16MLIIISFA As Short = &HC9S                        ' AI slave module, MechatroLink III AXT(SFA), Analog IN 16ch, 16 bit
    Public Const AXT_SIO_RDB32MSMLIII As Short = &HCAS                         ' DIO slave module, MechatroLink III M-SYSTEM, IN 16-Channel, OUT 16-Channel
    Public Const AXT_SIO_RAVI4MLII As Short = &HCBS                            ' DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    Public Const AXT_COM_234R As Short = &HD3S                                 ' COM-234R
    Public Const AXT_COM_484R As Short = &HD4S                                 ' COM-484R
    Public Const AXT_COM_234IDS As Short = &HD5S                               ' COM-234IDS
    Public Const AXT_COM_484IDS As Short = &HD6S                               ' COM-484IDS
    Public Const AXT_SIO_AO4F As Short = &HD7S                                 ' AO 4Ch, 16 bit
    Public Const AXT_SIO_AI8F As Short = &HD8S                                 ' AI 8Ch, 16 bit
    Public Const AXT_SIO_AI8AO4F As Short = &HD9S                              ' AI 8Ch, AO 4Ch, 16 bit
    Public Const AXT_SIO_HPC4 As Short = &HDAS                                 ' External Encoder module for 4Channel with Trigger function.    

    ' EtherCAT
    Public Const AXT_ECAT_MOTION As Short = &HE1S                              ' EtherCAT Motion Module
    Public Const AXT_ECAT_DIO As Short = &HE2S                                 ' EtherCAT DIO Module 
    Public Const AXT_ECAT_AIO As Short = &HE3S                                 ' EtherCAT AIO Module
    Public Const AXT_ECAT_SERIAL As Short = &HE4S                              ' EtherCAT Serial COM(RS232C) Module
    Public Const AXT_ECAT_COUPLER As Short = &HE5S                             ' EtherCAT Coupler Module
    Public Const AXT_ECAT_CNT As Short = &HE6S                                 ' EtherCAT Count Module        
    Public Const AXT_ECAT_UNKNOWN As Short = &HE7S                             ' EtherCAT Unknown Module
    Public Const AXT_SMC_4V04_A As Short = &HEAS                               ' Nx04_A
    'Public Const AXT_ECAT_ETC As Short = &HEBS                                ' EtherCAT ETC Module

    Public Const AXT_RT_SUCCESS As Short = 0                                    'API function executed successfully
    Public Const AXT_RT_OPEN_ERROR As Short = 1001                              'Library is not open
    Public Const AXT_RT_OPEN_ALREADY As Short = 1002                            'Library is already open
    Public Const AXT_RT_NOT_INITIAL As Short = 1052                             'Serial module is not initialized
    Public Const AXT_RT_NOT_OPEN As Short = 1053                                'Failed to initialize the library

    Public Const AXT_RT_NOT_SUPPORT_VERSION As Short = 1054                     'Hardware not supported
    Public Const AXT_RT_LOCK_FILE_MISMATCH As Short = 1055                      'Lock file mismatch
    Public Const AXT_RT_MASTER_VERSION_MISMATCH As Short = 1056                 'Library and EtherCAT Master versions do not match
    Public Const AXT_RT_NOT_RUN_EZMANAGER As Short = 1057                       'EzManager not running
    Public Const AXT_RT_NOT_FIND_BIN_FILE As Short = 1058                       'Can not find BIN file
    Public Const AXT_RT_NOT_FIND_ENI_FILE As Short = 1059                       'Can not find ENI file
    Public Const AXT_RT_NOT_FIND_CONFIG_FILE As Short = 1060                    'Can not find Config file
    Public Const AXT_RT_RTOS_OPEN_ERROR As Short = 1061                         'RTOS Open failed
    Public Const AXT_RT_SLAVE_CONFIG_ERROR As Short = 1062                      'RTOS Slave Config failed
    Public Const AXT_RT_SLAVE_OP_TIMEOUT_WARNING As Short = 1063                'Timeout occurs while waiting for slaves to enter OP mode
    Public Const AXT_RT_SLAVE_NOT_OP As Short = 1064                            'There is a Slave other than OP mode.
    
    Public Const AXT_RT_INVALID_HARDWARE As Short = 1100                        'Invalid board
    Public Const AXT_RT_INVALID_BOARD_NO As Short = 1101                        'Invalid board number
    Public Const AXT_RT_INVALID_MODULE_POS As Short = 1102                      'Invalid module location
    Public Const AXT_RT_INVALID_LEVEL As Short = 1103                           'Invalid level
    Public Const AXT_RT_INVALID_VARIABLE As Short = 1104                        'Invalid Variable
    Public Const AXT_RT_INVALID_MODULE_NO As Short = 1105                       'Invalid module number
    Public Const AXT_RT_INVALID_NO As Short = 1106                              'Invalid number
    Public Const AXT_RT_ERROR_VERSION_READ As Short = 1151                      'Failed to read library version
    Public Const AXT_RT_NETWORK_ERROR As Short = 1152                           'Hardware network error
    Public Const AXT_RT_NETWORK_LOCK_MISMATCH As Short = 1153                   'Board lock information does not match current scan information
    
    Public Const AXT_RT_1ST_BELOW_MIN_VALUE As Short = 1160                     'First parameter is below the minimum value
    Public Const AXT_RT_1ST_ABOVE_MAX_VALUE As Short = 1161                     'First parameter is above the maximum value
    Public Const AXT_RT_2ND_BELOW_MIN_VALUE As Short = 1170                     'Second parameter is below the minimum value
    Public Const AXT_RT_2ND_ABOVE_MAX_VALUE As Short = 1171                     'Second parameter is above the maximum value
    Public Const AXT_RT_3RD_BELOW_MIN_VALUE As Short = 1180                     'Third parameter is below the minimum value
    Public Const AXT_RT_3RD_ABOVE_MAX_VALUE As Short = 1181                     'Third parameter is above the maximum value
    Public Const AXT_RT_4TH_BELOW_MIN_VALUE As Short = 1190                     'Fourth parameter is below the minimum value
    Public Const AXT_RT_4TH_ABOVE_MAX_VALUE As Short = 1191                     'Fourth parameter is above the maximum value
    Public Const AXT_RT_5TH_BELOW_MIN_VALUE As Short = 1200                     'Fifth parameter is below the minimum value
    Public Const AXT_RT_5TH_ABOVE_MAX_VALUE As Short = 1201                     'Fifth parameter is above the maximum value
    Public Const AXT_RT_6TH_BELOW_MIN_VALUE As Short = 1210                     'Sixth parameter is below the minimum value
    Public Const AXT_RT_6TH_ABOVE_MAX_VALUE As Short = 1211                     'Sixth parameter is above the maximum value
    Public Const AXT_RT_7TH_BELOW_MIN_VALUE As Short = 1220                     'Seventh parameter is below the minimum value
    Public Const AXT_RT_7TH_ABOVE_MAX_VALUE As Short = 1221                     'Seventh parameter is above the maximum value
    Public Const AXT_RT_8TH_BELOW_MIN_VALUE As Short = 1230                     'Eighth parameter is below the minimum value
    Public Const AXT_RT_8TH_ABOVE_MAX_VALUE As Short = 1231                     'Eighth parameter is above the maximum value
    Public Const AXT_RT_9TH_BELOW_MIN_VALUE As Short = 1240                     'Ninth parameter is below the minimum value
    Public Const AXT_RT_9TH_ABOVE_MAX_VALUE As Short = 1241                     'Ninth parameter is above the maximum value
    Public Const AXT_RT_10TH_BELOW_MIN_VALUE As Short = 1250                    'Tenth parameter is above the minimum value
    Public Const AXT_RT_10TH_ABOVE_MAX_VALUE As Short = 1251                    'Tenth parameter is above the maximum value
    Public Const AXT_RT_11TH_BELOW_MIN_VALUE As Short = 1252                    'Eleventh parameter is smaller than the minimum value
    Public Const AXT_RT_11TH_ABOVE_MAX_VALUE As Short = 1253                    'Eleventh parameter is greater than the maximum value
    
    Public Const AXT_RT_AIO_OPEN_ERROR As Short = 2001                          'Filed to open AIO module
    Public Const AXT_RT_AIO_NOT_MODULE As Short = 2051                          'No AIO module
    Public Const AXT_RT_AIO_NOT_EVENT As Short = 2052                           'Failed to read AIO event
    Public Const AXT_RT_AIO_INVALID_MODULE_NO As Short = 2101                   'Invalid AIO module
    Public Const AXT_RT_AIO_INVALID_CHANNEL_NO As Short = 2102                  'Invalid AIO channel number
    Public Const AXT_RT_AIO_INVALID_USE As Short = 2106                         'Can not use AIO
    Public Const AXT_RT_AIO_INVALID_TRIGGER_MODE As Short = 2107                'Invalid trigger mode
    Public Const AXT_RT_AIO_EXTERNAL_DATA_EMPTY As Short = 2108                 'No external data value
    Public Const AXT_RT_AIO_INVALID_VALUE As Short = 2109                       'Invalid value setting
    Public Const AXT_RT_AIO_UPG_ALEADY_ENABLED As Short = 2110                  'AO UPG function is already enabled
    
    Public Const AXT_RT_DIO_OPEN_ERROR As Short = 3001                          'Failed to open DIO module
    Public Const AXT_RT_DIO_NOT_MODULE As Short = 3051                          'No DIO module
    Public Const AXT_RT_DIO_NOT_INTERRUPT As Short = 3052                       'DIO Interrupt not set
    Public Const AXT_RT_DIO_INVALID_MODULE_NO As Short = 3101                   'Invalid DIO module number
    Public Const AXT_RT_DIO_INVALID_OFFSET_NO As Short = 3102                   'Invalid DIO OFFSET number
    Public Const AXT_RT_DIO_INVALID_LEVEL As Short = 3103                       'Invalid DIO level
    Public Const AXT_RT_DIO_INVALID_MODE As Short = 3104                        'Invalid DIO mode
    Public Const AXT_RT_DIO_INVALID_VALUE As Short = 3105                       'Invalid setting value
    Public Const AXT_RT_DIO_INVALID_USE As Short = 3106                         'Can not use DIO API function

    Public Const AXT_RT_CNT_OPEN_ERROR As Short = 3201                          'Fail to open CND module
    Public Const AXT_RT_CNT_NOT_MODULE As Short = 3251                          'No CNT module
    Public Const AXT_RT_CNT_NOT_INTERRUPT As Short = 3252                       'CNT Interrupt not set
    Public Const AXT_RT_CNT_INVALID_MODULE_NO As Short = 3301                   'Invalid CNT module number
    Public Const AXT_RT_CNT_INVALID_CHANNEL_NO As Short = 3302                  'Invalid CNT channel number
    Public Const AXT_RT_CNT_INVALID_OFFSET_NO As Short = 3303                   'Invalid CNT OFFSET number
    Public Const AXT_RT_CNT_INVALID_LEVEL As Short = 3304                       'Invalid CNT level
    Public Const AXT_RT_CNT_INVALID_MODE As Short = 3305                        'Invalid CNT mode
    Public Const AXT_RT_CNT_INVALID_VALUE As Short = 3306                       'Invalid setting value
    Public Const AXT_RT_CNT_INVALID_USE As Short = 3307                         'Can not use CNT API function
    
    Public Const AXT_RT_COM_OPEN_ERROR As Short = 3401                          'COM port open failure
    Public Const AXT_RT_COM_NOT_OPEN As Short = 3402                            'COM Port Not Opened
    Public Const AXT_RT_COM_ALREADY_IN_USE As Short = 3403                      'Using COM port
    Public Const AXT_RT_COM_NOT_MODULE As Short = 3451                          'No COM port
    Public Const AXT_RT_COM_NOT_INTERRUPT As Short = 3452                       'COM interrupt not set
    Public Const AXT_RT_COM_INVALID_MODULE_NO As Short = 3501                   'Invalid COM module number
    Public Const AXT_RT_COM_INVALID_PORT_NO As Short = 3502                     'Invalid channel number
    Public Const AXT_RT_COM_INVALID_OFFSET_NO As Short = 3503                   'Invalid COM OFFSET number
    Public Const AXT_RT_COM_INVALID_LEVEL As Short = 3504                       'Invalid COM level
    Public Const AXT_RT_COM_INVALID_MODE As Short = 3505                        'Invalid COM mode
    Public Const AXT_RT_COM_INVALID_VALUE As Short = 3506                       'Invalid value setting
    Public Const AXT_RT_COM_INVALID_USE As Short = 3507                         'Can not use COM function
    Public Const AXT_RT_COM_INVALID_BAUDRATE As Short = 3508                    'Invalid baudrate setting
    Public Const AXT_RT_MOTION_OPEN_ERROR As Short = 4001                       'Failed to open motion library
    Public Const AXT_RT_MOTION_NOT_MODULE As Short = 4051                       'No motion module is installed in the system
    Public Const AXT_RT_MOTION_NOT_INTERRUPT As Short = 4052                    'Failed to read the result of interrupt
    Public Const AXT_RT_MOTION_NOT_INITIAL_AXIS_NO As Short = 4053              'Failed to initialize the motion of corresponding axis
    Public Const AXT_RT_MOTION_NOT_IN_CONT_INTERPOL As Short = 4054             'Command to stop continuous interpolation while not in continuous interpolation motion
    Public Const AXT_RT_MOTION_NOT_PARA_READ As Short = 4055                    'Failed to load parameters for home return drive
    Public Const AXT_RT_MOTION_INVALID_AXIS_NO As Short = 4101                  'Corresponding axis does not exist
    Public Const AXT_RT_MOTION_INVALID_METHOD As Short = 4102                   'Invalid setting for corresponding axis drive
    Public Const AXT_RT_MOTION_INVALID_USE As Short = 4103                      'Invalid setting for 'uUse                      'parameter
    Public Const AXT_RT_MOTION_INVALID_LEVEL As Short = 4104                    'Invalid setting for 'uLevel                      'parameter
    Public Const AXT_RT_MOTION_INVALID_BIT_NO As Short = 4105                   'Invalid setting for general purpose input/output bit
    Public Const AXT_RT_MOTION_INVALID_STOP_MODE As Short = 4106                'Invalid setting values for motion stop mode
    Public Const AXT_RT_MOTION_INVALID_TRIGGER_MODE As Short = 4107             'Invalid setting for trigger setting mode
    Public Const AXT_RT_MOTION_INVALID_TRIGGER_LEVEL As Short = 4108            'Invalid setting for trigger output level
    Public Const AXT_RT_MOTION_INVALID_SELECTION As Short = 4109                ''uSelection'parameter is set to a value other than COMMAND or ACTUAL
    Public Const AXT_RT_MOTION_INVALID_TIME As Short = 4110                     'Invalid setting for Trigger output time value
    Public Const AXT_RT_MOTION_INVALID_FILE_LOAD As Short = 4111                'Failed to load the file containing motion setting values
    Public Const AXT_RT_MOTION_INVALID_FILE_SAVE As Short = 4112                'Failed to save the file containing motion setting values
    Public Const AXT_RT_MOTION_INVALID_VELOCITY As Short = 4113                 'Motion error occurred since the motion drive velocity value is set as zero
    Public Const AXT_RT_MOTION_INVALID_ACCELTIME As Short = 4114                'Motion error occurred since motion drive acceleration time value is set as zero
    Public Const AXT_RT_MOTION_INVALID_PULSE_VALUE As Short = 4115              'Input pulse value is set to a value less than zero when setting motion unit
    Public Const AXT_RT_MOTION_INVALID_NODE_NUMBER As Short = 4116              'Called position or velocity override function while not in motion
    Public Const AXT_RT_MOTION_INVALID_TARGET As Short = 4117                   'Flag indicating the cause of multi axis motion stop
    Public Const AXT_RT_MOTION_ERROR_IN_NONMOTION As Short = 4151               'Not in motion drive when it should be
    Public Const AXT_RT_MOTION_ERROR_IN_MOTION As Short = 4152                  'Called another motion drive function before the completion of current motion
    Public Const AXT_RT_MOTION_ERROR As Short = 4153                            'Error occurred during the execution of multi axis motion stop function
    Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE As Short = 4154              'Gantry-enable is activated again while in motion with gantry enabled
    Public Const AXT_RT_MOTION_ERROR_GANTRY_AXIS As Short = 4155                'Invalid input of gantry axis master channel (axis) number (starting from zero)
    Public Const AXT_RT_MOTION_ERROR_MASTER_SERVOON As Short = 4156             'Servo ON is not enabled for the master axis
    Public Const AXT_RT_MOTION_ERROR_SLAVE_SERVOON As Short = 4157              'Servo ON is not enabled for the slave axis
    Public Const AXT_RT_MOTION_INVALID_POSITION As Short = 4158                 'Not in a valid position
    Public Const AXT_RT_ERROR_NOT_SAME_MODULE As Short = 4159                   'Not in the same module
    Public Const AXT_RT_ERROR_NOT_SAME_BOARD As Short = 4160                    'Not in the same board
    Public Const AXT_RT_ERROR_NOT_SAME_PRODUCT As Short = 4161                  'When products are different each other
    Public Const AXT_RT_NOT_CAPTURED As Short = 4162                            'Failed to capture the position
    Public Const AXT_RT_ERROR_NOT_SAME_IC As Short = 4163                       'Not in the same chip
    Public Const AXT_RT_ERROR_NOT_GEARMODE As Short = 4164                      'Failed to change to the gear mode
    Public Const AXT_ERROR_CONTI_INVALID_AXIS_NO As Short = 4165                'Invalid axis during continuous interpolation axies mapping
    Public Const AXT_ERROR_CONTI_INVALID_MAP_NO As Short = 4166                 'Invalid mapping number during continuous interpolation mapping
    Public Const AXT_ERROR_CONTI_EMPTY_MAP_NO As Short = 4167                   'Continuous interpolation mapping number is empty
    Public Const AXT_RT_MOTION_ERROR_CACULATION As Short = 4168                 'Error in calculation
    Public Const AXT_RT_ERROR_MOVE_SENSOR_CHECK As Short = 4169                 'Error sensor (Alarm, EMG, Limit, etc.) is detected before continuous interpolation drive
    
    Public Const AXT_ERROR_HELICAL_INVALID_AXIS_NO As Short = 4170              'Invalid axis for helical axis mapping
    Public Const AXT_ERROR_HELICAL_INVALID_MAP_NO As Short = 4171               'Invalid mapping number for helical mapping
    Public Const AXT_ERROR_HELICAL_EMPTY_MAP_NO As Short = 4172                 'Helical mapping number is empty
    
    Public Const AXT_ERROR_SPLINE_INVALID_AXIS_NO As Short = 4180               'Invalid axis for spline axis mapping
    Public Const AXT_ERROR_SPLINE_INVALID_MAP_NO As Short = 4181                'Invalid mapping number for spline mapping
    Public Const AXT_ERROR_SPLINE_EMPTY_MAP_NO As Short = 4182                  'Spline Mapping number is empty
    Public Const AXT_ERROR_SPLINE_NUM_ERROR As Short = 4183                     'Spline point value is inapplicable
    Public Const AXT_RT_MOTION_INTERPOL_VALUE As Short = 4184                   'Invalid input value for interpolation
    Public Const AXT_RT_ERROR_NOT_CONTIBEGIN As Short = 4185                    'CONTIBEGIN function is not called in continuous interpolation
    Public Const AXT_RT_ERROR_NOT_CONTIEND As Short = 4186                      'CONTIEND function is not called in continuous interpolation
    
    Public Const AXT_RT_MOTION_HOME_SEARCHING As Short = 4201                   'Other function is called while in home search motion
    Public Const AXT_RT_MOTION_HOME_ERROR_SEARCHING As Short = 4202             'Home search motion is forced to stop by the user or something from external
    Public Const AXT_RT_MOTION_HOME_ERROR_START As Short = 4203                 'Failed to start home search drive due to Initialization  problem
    Public Const AXT_RT_MOTION_HOME_ERROR_GANTRY As Short = 4204                'Failed to execute Gantry enable during home search motion

    Public Const AXT_RT_MOTION_READ_ALARM_WAITING As Short = 4210               'Waiting for alarm code result from SERVOPACK
    Public Const AXT_RT_MOTION_READ_ALARM_NO_REQUEST As Short = 4211            'Alarm code return command is not issued to SERVOPACK
    Public Const AXT_RT_MOTION_READ_ALARM_TIMEOUT As Short = 4212               'Servo pack alarm read timeout (1sec or more)
    Public Const AXT_RT_MOTION_READ_ALARM_FAILED As Short = 4213                'Servo pack alarm read failure
    Public Const AXT_RT_MOTION_READ_ALARM_UNKNOWN As Short = 4220               'Unknown alarm code
    Public Const AXT_RT_MOTION_READ_ALARM_FILES As Short = 4221                 'Alarm information file does not exist at the specified position
    Public Const AXT_RT_MOTION_READ_ALARM_NOT_DETECTED As Short = 4222          'No alarms
    Public Const AXT_RT_MOTION_POSITION_OUTOFBOUND As Short = 4251              'Configured position is either above the maximum value or below the minimum value
    Public Const AXT_RT_MOTION_PROFILE_INVALID As Short = 4252                  'Invalid setting for velocity profile
    Public Const AXT_RT_MOTION_VELOCITY_OUTOFBOUND As Short = 4253              'Configured velocity is either above the maximum value or below the minimum value
    Public Const AXT_RT_MOTION_MOVE_UNIT_IS_ZERO As Short = 4254                'Unit of the motion values is set as zero
    Public Const AXT_RT_MOTION_SETTING_ERROR As Short = 4255                    'Invalid setting for Velocity, Acceleration, Jerk, or Profile
    Public Const AXT_RT_MOTION_IN_CONT_INTERPOL As Short = 4256                 'Execution of motion start or restart function before the completion of current continuous interpolated motion
    Public Const AXT_RT_MOTION_DISABLE_TRIGGER As Short = 4257                  'Trigger output is disabled
    Public Const AXT_RT_MOTION_INVALID_CONT_INDEX As Short = 4258               'Invalid setting for continuous interpolation index value
    Public Const AXT_RT_MOTION_CONT_QUEUE_FULL As Short = 4259                  'Continuous Interpolation queue of motion chip is full
    Public Const AXT_RT_PROTECTED_DURING_SERVOON As Short = 4260                'Protected during servo-on
    Public Const AXT_RT_HW_ACCESS_ERROR As Short = 4261                         'Failed memory Read / Write
    Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1 As Short = 4262            'DPRAM Command Write fail Level1
    Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2 As Short = 4263            'DPRAM Command Write fail Level2
    Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3 As Short = 4264            'DPRAM Command Write fail Level3
    Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1 As Short = 4265             'DPRAM Command Read fail Level1
    Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2 As Short = 4266             'DPRAM Command Read fail Level2
    Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3 As Short = 4267             'DPRAM Command Read fail Level3
    
    Public Const AXT_RT_COMPENSATION_SET_PARAM_FIRST As Short = 4300            'The first of the calibration parameters is set incorrectly
    Public Const AXT_RT_COMPENSATION_NOT_INIT As Short = 4301                   'Calibration table function not initialized   
    Public Const AXT_RT_COMPENSATION_POS_OUTOFBOUND As Short = 4302             'Position value is not in range
    Public Const AXT_RT_COMPENSATION_BACKLASH_NOT_INIT As Short = 4303          'Backlash compensation function not initialized
    Public Const AXT_RT_COMPENSATION_INVALID_ENTRY As Short = 4304              'The entry number is invalid.

    Public Const AXT_RT_SEQ_NOT_IN_SERVICE As Short = 4400                      'Resource allocation failure while executing sequential drive function
    Public Const AXT_ERROR_SEQ_INVALID_MAP_NO As Short = 4401                   'Sequence drive function Running mapping number or more.
    Public Const AXT_ERROR_INVALID_AXIS_NO As Short = 4402                      'Above axis number in function setting parameter.
    Public Const AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN As Short = 4403                'The sequential driven node input start function was not called.
    Public Const AXT_RT_ERROR_NOT_SEQ_NODE_END As Short = 4404                  'The sequential driven node input end function was not called.
    Public Const AXT_RT_ERROR_NO_NODE As Short = 4405                           'No sequential drive node input.
    Public Const AXT_RT_ERROR_SEQ_STOP_TIMEOUT As Short = 4406                  'Timeout occurred.
    Public Const AXT_RT_ERROR_INVALID_SEQ_MASTER_AXIS_NO As Short = 4407        'Sequential drive Master axis is invalid.

    Public Const AXT_RT_ERROR_RING_COUNTER_ENABLE As Short = 4420               'Ring Counter function is in use
    Public Const AXT_RT_ERROR_RING_COUNTER_OUT_OF_RANGE As Short = 4421         'Ring Counter In Use Out-of-Range Command Location Invocation (POS_ABS_LONG_MODE or POS_ABS_SHORT_MODE)
    Public Const AXT_RT_ERROR_SOFT_LIMIT_ENABLE As Short = 4430                 'Software Limit feature is enabled

    Public Const AXT_RT_M3_COMMUNICATION_FAILED As Short = 4500             ' ML3 Only 
    Public Const AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3 As Short = 4501        ' ML3 Only
    Public Const AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL As Short = 4502      ' ML3 Only
    Public Const AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL As Short = 4503     ' ML3 Only
    Public Const AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO As Short = 4504  ' ML3 Only
    Public Const AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE As Short = 4505  ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_INPUT_ACCEL As Short = 4506          ' ML3 Only
    Public Const AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE As Short = 4507  ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_INPUT_DECEL As Short = 4508          ' ML3 Only
    Public Const AXT_RT_MOTION_SAME_START_AND_CENTER_POS As Short = 4509    ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_JERK As Short = 4510                 ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_INPUT_VALUE As Short = 4511          ' ML3 Only
    Public Const AXT_RT_MOTION_NOT_SUPPORT_PROFILE As Short = 4512          ' ML3 Only
    Public Const AXT_RT_MOTION_INPOS_UNUSED As Short = 4513                 ' ML3 Only
    Public Const AXT_RT_MOTION_AXIS_IN_SLAVE_STATE As Short = 4514          ' ML3 Only
    Public Const AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD As Short = 4515      ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_IN_ALARM As Short = 4516               ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_IN_EMGN As Short = 4517                ' ML3 Only
    Public Const AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO As Short = 4518      ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS As Short = 4519     ' ML3 Only
    Public Const AXT_RT_MOTION_CONTI_QUEUE_FULL As Short = 4521             ' ML3 Only
    Public Const AXT_RT_MOTION_SAME_START_AND_END_POSITION As Short = 4522  ' ML3 Only
    Public Const AXT_RT_MOTION_INVALID_ANGLE As Short = 4523                ' ML3 Only
    Public Const AXT_RT_MOTION_CONTI_QUEUE_EMPTY As Short = 4524            ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE As Short = 4525            ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_GEAR_AXIS As Short = 4526              ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE As Short = 4527       ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE As Short = 4528         ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL As Short = 4529     ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL As Short = 4530       ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE As Short = 4531        ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE As Short = 4532          ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME As Short = 4533      ' ML3 Only
    Public Const AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL As Short = 4534       ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT As Short = 4535       ' ML3 Only
    Public Const AXT_RT_MOTION_OVERFLOW_POSITION As Short = 4536            ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS As Short = 4537   ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE As Short = 4538   ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_IN_SERVO_OFF As Short = 4539           ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_POSITIVE_LIMIT As Short = 4540         ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT As Short = 4541         ' ML3 Only
    Public Const AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM As Short = 4542 ' ML3 Only
    Public Const AXT_RT_PROTECTED_DURING_INMOTION As Short = 4543           ' ML3 Only


    Public Const AXT_RT_DATA_FLASH_NOT_EXIST As Short = 5000
    Public Const AXT_RT_DATA_FLASH_BUSY As Short = 5001
    
    Public Const AXT_RT_QUEUE_CMD_ERROR As Short = 5010
    Public Const AXT_RT_QUEUE_CMD_WAIT_ERROR As Short = 5011
    Public Const AXT_RT_QUEUE_CMD_WAIT_TIMEOUT As Short = 5012

    Public Const AXT_RT_QUEUE_RSP_ERROR As Short = 5015
    Public Const AXT_RT_QUEUE_RSP_WAIT_ERROR As Short = 5016
    Public Const AXT_RT_QUEUE_RSP_WAIT_TIMEOUT As Short = 5017

    Public Const AXT_RT_MOTION_STILL_CONTI_MOTION As Short = 5018                               ' During continuous interpolation drive, calls such as WriteClear and SetAxisMpa were called.
    Public Const AXT_RT_MOTION_INVALD_SET As Short = 6000
    Public Const AXT_RT_MOTION_INVALD_RESET As Short = 6001
    Public Const AXT_RT_MOTION_INVALD_ENABLE As Short = 6002
    
    Public Const AXT_RT_LICENSE_INVALID As Short                                  = 6500        ' Invalid License

    Public Const AXT_RT_MONITOR_IN_OPERATION As Short                             = 6600        ' Monitor function currently active
    Public Const AXT_RT_MONITOR_NOT_OPERATION As Short                            = 6601        ' Monitor function currently inactive
    Public Const AXT_RT_MONITOR_EMPTY_QUEUE As Short                              = 6602        ' Empty Monitor data queue
    Public Const AXT_RT_MONITOR_INVALID_TRIGGER_OPTION As Short                   = 6603        ' Trigger setting is not valid
    Public Const AXT_RT_MONITOR_EMPTY_ITEM As Short                               = 6604        ' Empty item
    Public Const AXT_RT_MACRO_INVALID_MACRO_NO As Short         = 6700                                  
    Public Const AXT_RT_MACRO_INVALID_NODE_NO As Short          = 6701
    Public Const AXT_RT_MACRO_INVALID_STOP_MODE As Short        = 6702
    Public Const AXT_RT_MACRO_MEMORY_MISMATCH As Short          = 6703
    Public Const AXT_RT_MACRO_CONTROL_LOCKED As Short           = 6704
    Public Const AXT_RT_MACRO_NOT_NODE_BEGIN As Short           = 6710
    Public Const AXT_RT_MACRO_NOT_NODE_END As Short             = 6711
    Public Const AXT_RT_MACRO_ALREADY_BEGIN As Short            = 6712
    Public Const AXT_RT_MACRO_NODE_EMPTY As Short               = 6713
    Public Const AXT_RT_MACRO_IN_OPERATION As Short             = 6714
    Public Const AXT_RT_MACRO_NOT_OPERATION As Short            = 6715
    Public Const AXP_RT_MACRO_NOT_SUPPORT_FUNCTION As Short     = 6716
    Public Const AXP_RT_MACRO_NODE_FULL As Short                = 6717
    Public Const AXP_RT_MACRO_NODE_CHECK_ERROR As Short         = 6720
    Public Const AXT_RT_MACRO_NOT_CHECKED As Short              = 6721

    Public Const AXT_MK_RT_INVALID_AXIS As Short                                  = 7100
    Public Const AXT_MK_RT_INVALID_AXIS_SIZE As Short                             = 7101
    Public Const AXT_MK_RT_INVALID_COORD As Short                                 = 7102
    Public Const AXT_MK_RT_INVALID_COORD_SIZE As Short                            = 7103
    Public Const AXT_MK_RT_INVALID_AXIS_MAP As Short                              = 7104
    Public Const AXT_MK_RT_INVALID_AXIS_MAP_SIZE As Short                         = 7105
    Public Const AXT_MK_RT_INVALID_VEL As Short                                   = 7106
    Public Const AXT_MK_RT_INVALID_END_VEL As Short                               = 7107
    Public Const AXT_MK_RT_INVALID_ACCEL As Short                                 = 7108
    Public Const AXT_MK_RT_INVALID_DECEL As Short                                 = 7109
    Public Const AXT_MK_RT_INVALID_ABS_REL As Short                               = 7110
    Public Const AXT_MK_RT_INVALID_PROFILE As Short                               = 7111
    Public Const AXT_MK_RT_INVALID_STOP_DECEL As Short                            = 7112
    Public Const AXT_MK_RT_INVALID_STOP_TIME As Short                             = 7113
    Public Const AXT_MK_RT_INVALID_ACCEL_JERK_RATE As Short                       = 7114
    Public Const AXT_MK_RT_INVALID_DECEL_JERK_RATE As Short                       = 7115
    Public Const AXT_MK_RT_INVALID_ACCEL_UNIT As Short                            = 7116
    Public Const AXT_MK_RT_INVALID_DISTANCE As Short                              = 7117
    Public Const AXT_MK_RT_INVALID_ANGLE As Short                                 = 7118
    Public Const AXT_MK_RT_INVALID_BIT As Short                                   = 7119
    Public Const AXT_MK_RT_INVALID_PORT As Short                                  = 7120
    Public Const AXT_MK_RT_INVALID_SPLINE_INDEX As Short                          = 7121
    Public Const AXT_MK_RT_INVALID_THREAD As Short                                = 7122
    Public Const AXT_MK_RT_INVALID_TIMER As Short                                 = 7123
    Public Const AXT_MK_RT_INVALID_SEGMENT_COUNT As Short                         = 7124
    Public Const AXT_MK_RT_INVALID_SEGMENT_NO As Short                            = 7125
    Public Const AXT_MK_RT_INVALID_NODE_NO As Short                               = 7126
    Public Const AXT_MK_RT_INVALID_HWQ_COUNT As Short                             = 7127
    Public Const AXT_MK_RT_INVALID_NODE_SIZE As Short                             = 7128
    Public Const AXT_MK_RT_INVALID_STOP_NODE_SIZE As Short                        = 7129
    Public Const AXT_MK_RT_INVALID_SPLINE_SIZE As Short                           = 7130
    Public Const AXT_MK_RT_INVALID_LINE_LINE_FILLET As Short                      = 7131
    Public Const AXT_MK_RT_INVALID_LINE_ARC_FILLET As Short                       = 7132
    Public Const AXT_MK_RT_INVALID_ARC_LINE_FILLET As Short                       = 7133
    Public Const AXT_MK_RT_INVALID_ARC_ARC_FILLET As Short                        = 7134
    Public Const AXT_MK_RT_INVALID_RESET_FILLET As Short                          = 7135
    Public Const AXT_MK_RT_INVALID_TASK As Short                                  = 7136
    Public Const AXT_MK_RT_INVALID_ROUND_INDEX As Short                           = 7137
    Public Const AXT_MK_RT_INVALID_LOG_DATA As Short                              = 7138
    Public Const AXT_MK_RT_INVALID_LOG10_DATA As Short                            = 7139
    Public Const AXT_MK_RT_INVALID_PORT_NO As Short                               = 7140
    Public Const AXT_MK_RT_INVALID_BAUD_RATE As Short                             = 7141
    Public Const AXT_MK_RT_INVALID_STOP_BIT As Short                              = 7142
    Public Const AXT_MK_RT_INVALID_PARITY As Short                                = 7143
    Public Const AXT_MK_RT_INVALID_EDGE As Short                                  = 7144
    Public Const AXT_MK_RT_INVALID_STOP_MODE As Short                             = 7145
    Public Const AXT_MK_RT_INVALID_TRIGGER_TIME As Short                          = 7146
    Public Const AXT_MK_RT_INVALID_TRIGGER_LEVEL As Short                         = 7147
    Public Const AXT_MK_RT_INVALID_TRIGGER_SELECT As Short                        = 7148
    Public Const AXT_MK_RT_INVALID_TRIGGER_INTERRUPT As Short                     = 7149
    Public Const AXT_MK_RT_INVALID_TRIGGER_METHOD As Short                        = 7150
    Public Const AXT_MK_RT_INVALID_TRIGGER_POSITION As Short                      = 7151
    Public Const AXT_MK_RT_INVALID_TRIGGER_INDEX As Short                         = 7152
    Public Const AXT_MK_RT_INVALID_ECAM_DATA As Short                             = 7153
    Public Const AXT_MK_RT_INVALID_ECAM_POSITION As Short                         = 7154
    Public Const AXT_MK_RT_INVALID_EGEAR_SIZE As Short                            = 7155
    Public Const AXT_MK_RT_INVALID_INDEX As Short                                 = 7156
    Public Const AXT_MK_RT_INVALID_MOTION_MODE As Short                           = 7157
    Public Const AXT_MK_RT_INVALID_SIGNAL As Short                                = 7158
    Public Const AXT_MK_RT_INVALID_STOP_DISTANCE As Short                         = 7159
    Public Const AXT_MK_RT_INVALID_DIRECTION As Short                             = 7160
    Public Const AXT_MK_RT_INVALID_ZERO_VELOCITY As Short                         = 7161
    Public Const AXT_MK_RT_INVALID_COORDINATE_INMOTION As Short                   = 7162
    Public Const AXT_MK_RT_INVALID_COORDINATE_MOTIONDONE As Short                 = 7163
    Public Const AXT_MK_RT_INVALID_BLENDING_MODE As Short                         = 7164
    Public Const AXT_MK_RT_INVALID_BLENDING_VALUE As Short                        = 7165
    Public Const AXT_MK_RT_INVALID_BLENDING_RATIO As Short                        = 7166
    Public Const AXT_MK_RT_INVALID_EGEAR_RATIO As Short                           = 7167
    Public Const AXT_MK_RT_INVALID_SLAVE_AXIS As Short                            = 7168
    Public Const AXT_MK_RT_INVALID_OPERATION_MODE As Short                        = 7169

    Public Const AXT_MK_RT_INVALID_CONTIQ_DISABLE As Short                        = 7170
    Public Const AXT_MK_RT_INVALID_CONTIQ_MODE As Short                           = 7171
    Public Const AXT_MK_RT_INVALID_CONTIQ_ANGLE As Short                          = 7172
    Public Const AXT_MK_RT_INVALID_CONTIQ_VELRATE As Short                        = 7173
    Public Const AXT_MK_RT_INVALID_CONTIQ_FILLET As Short                         = 7174

    Public Const AXT_MK_RT_CONTIQ_AUTO_VEL As Short                               = 7175
    Public Const AXT_MK_RT_CONTIQ_AUTO_ARC As Short                               = 7176
    Public Const AXT_MK_RT_CONTIQ_LINE As Short                                   = 7177
    Public Const AXT_MK_RT_CONTIQ_CIRCLE As Short                                 = 7178
    Public Const AXT_MK_RT_CONTIQ_ARC As Short                                    = 7179
    Public Const AXT_MK_RT_CONTIQ_SYNC_SLAVE As Short                             = 7180
    Public Const AXT_MK_RT_INVALID_SEGMENT_OUTPUT_SIZE As Short                   = 7181
    Public Const AXT_MK_RT_INVALID_SEGMENT_NUMBER As Short                        = 7182
    Public Const AXT_MK_RT_INVALID_TRIG_COUNT As Short                            = 7183
    Public Const AXT_MK_RT_INVALID_TRIG_TIME As Short                             = 7184
    Public Const AXT_MK_RT_NOT_CAPTURED As Short                                  = 7185
    Public Const AXT_MK_RT_INVALID_CAPTURE_INDEX As Short                         = 7186
    Public Const AXT_MK_RT_INVALID_LEVEL As Short                                 = 7187
    Public Const AXT_MK_RT_INVALID_SEGMENT_OUTPUT_MODE As Short                   = 7188
    Public Const AXT_MK_RT_INVALID_SEGMENT_OUTPUT_VALUE As Short                  = 7189
    Public Const AXT_MK_RT_INVALID_SEGMENT_OUTPUT_RATIO As Short                  = 7190

    Public Const AXT_MK_RT_INVALID_SPLINE_POINT_SIZE As Short                     = 7191
    Public Const AXT_MK_RT_INVALID_INMOTION As Short                              = 7192

    Public Const AXT_MK_RT_ENABLE_CONTIQ As Short                                 = 7200
    Public Const AXT_MK_RT_DISABLE_CONTIQ As Short                                = 7201
    Public Const AXT_MK_RT_ENABLE_CONTIQ_SYNC As Short                            = 7202
    Public Const AXT_MK_RT_DISABLE_CONTIQ_SYNC As Short                           = 7203
    Public Const AXT_MK_RT_ENABLE_CONTI As Short                                  = 7204
    Public Const AXT_MK_RT_DISABLE_CONTI As Short                                 = 7205
    Public Const AXT_MK_RT_ENABLE_EGEAR As Short                                  = 7206
    Public Const AXT_MK_RT_DISABLE_EGEAR As Short                                 = 7207
    Public Const AXT_MK_RT_ENABLE_TASK As Short                                   = 7208
    Public Const AXT_MK_RT_DISABLE_TASK As Short                                  = 7209
    Public Const AXT_MK_RT_DISABLE_PORT_NO As Short                               = 7210

    Public Const AXT_MK_RT_ALREADY_OPEN As Short                                  = 7300
    Public Const AXT_MK_RT_ALREADY_CLOSE As Short                                 = 7301

    Public Const AXT_MK_RT_ERROR_HOME As Short                                    = 7400
    Public Const AXT_MK_RT_ERROR_MOTION As Short                                  = 7401
    Public Const AXT_MK_RT_ERROR_INSTOPPING As Short                              = 7402
    Public Const AXT_MK_RT_ERROR_TIME_OUT As Short                                = 7403
    Public Const AXT_MK_RT_ERROR_BUFFER_FULL As Short                             = 7404
    Public Const AXT_MK_RT_ERROR_DATA_CREATE As Short                             = 7405
    Public Const AXT_MK_RT_ERROR_CALCULATION As Short                             = 7406

    Public Const AXT_MK_RT_ERROR_QUEUE_FULL As Short                              = 7500
    Public Const AXT_MK_RT_ERROR_QUEUE_NULL As Short                              = 7501

    Public Const AXT_MK_RT_ERROR_ECAM_TABLE As Short                              = 7502

    Public Const AXT_MK_RT_ERROR_SPLINE_POSITION As Short                         = 7503

    Public Const AXT_MK_RT_INVALID_CIRCULAR_POINT As Short                        = 7510
    Public Const AXT_MK_RT_INVALID_POINT As Short                                 = 7511
    Public Const AXT_MK_RT_INVALID_QUEUE_SIZE As Short                            = 7512
    Public Const AXT_MK_RT_INVALID_POSITION As Short                              = 7513
    Public Const AXT_MK_RT_INVALID_ROTATION As Short                              = 7514

    Public Const AXT_MK_RT_INVALID_TABLE As Short                                 = 7600
    Public Const AXT_MK_RT_INVALID_TABLE_NO As Short                              = 7601
    Public Const AXT_MK_RT_INVALID_TABLE_DATA As Short                            = 7602
    Public Const AXT_MK_RT_INVALID_POSITION_SIZE As Short                         = 7603

    Public Const AXT_MK_RT_INVALID_TABLE_ENABLED As Short                         = 7604
    Public Const AXT_MK_RT_INVALID_TABLE_NOT_ENABLED As Short                     = 7605
    Public Const AXT_MK_RT_INVALID_TABLE_NONE As Short                            = 7606
    Public Const AXT_MK_RT_INVALID_GET_TABLE As Short                             = 7607
    Public Const AXT_MK_RT_INVALID_ENABLE_TABLE As Short                          = 7608
    Public Const AXT_MK_RT_INVALID_DISABLE_TABLE As Short                         = 7609

    Public Const AXT_MK_RT_INVALID_SET As Short                                   = 7610
    Public Const AXT_MK_RT_INVALID_RESET As Short                                 = 7611
    Public Const AXT_MK_RT_INVALID_ENABLE As Short                                = 7612

    Public Const AXT_MK_RT_NOT_SUPPORT As Short                                   = 7900
    Public Const AXT_MK_RT_ERROR As Short                                         = 7901
    Public Const AXT_MK_RT_INVLID_FUNCTION_TYPE As Short                          = 7902

    Public Const AXT_MK_RT_INVALID_ROBOT_SIZE As Short                            = 7700
    Public Const AXT_MK_RT_INVALID_ROBOT_AXIS_SIZE As Short                       = 7701
    Public Const AXT_MK_RT_INVALID_ROBOT_COORD_SIZE As Short                      = 7702
    Public Const AXT_MK_RT_INVALID_ROBOT_NO As Short                              = 7703
    Public Const AXT_MK_RT_INVALID_ROBOT_COORD As Short                           = 7704
    Public Const AXT_MK_RT_INVALID_ROBOT_LIMIT As Short                           = 7705
    Public Const AXT_MK_RT_INVALID_ROBOT_POS_LIMIT As Short                       = 7706
    Public Const AXT_MK_RT_INVALID_ROBOT_NEG_LIMIT As Short                       = 7707
    Public Const AXT_MK_RT_INVALID_ROBOT_VEL_LIMIT As Short                       = 7708
    Public Const AXT_MK_RT_INVALID_ROBOT_ACCEL_LIMIT As Short                     = 7709
    Public Const AXT_MK_RT_INVALID_ROBOT_DECEL_LIMIT As Short                     = 7710
    Public Const AXT_MK_RT_ERROR_ROBOT_CALCULATION As Short                       = 7711
    Public Const AXT_MK_RT_INVALID_FRAME As Short                                 = 7712
    Public Const AXT_MK_RT_INVALID_FRAME_NO As Short                              = 7713
    Public Const AXT_MK_RT_INVALID_FRAME_TYPE As Short                            = 7714
    Public Const AXT_MK_RT_INVALID_OBJECT_NO As Short                             = 7715
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC As Short                            = 7716
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC_MOTION As Short                     = 7717
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC_ENABLE As Short                     = 7718
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC_DISABLE As Short                    = 7719
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC_MOTION_MODE As Short                = 7720
    Public Const AXT_MK_RT_INVALID_ROBOT_SYNC_WORK_COORD As Short                 = 7721
    Public Const AXT_MK_RT_INVALID_CAPTURE_POS_NO As Short                        = 7722
    
    Public Const AXT_MK_RT_INVALID_ROBOT_CAPTURE_POS As Short                     = 7730
    Public Const AXT_MK_RT_INVALID_ROBOT_AXIS As Short                            = 7731
    Public Const AXT_MK_RT_INVALID_WORK_NEGATIVE_LIMIT As Short                   = 7732
    Public Const AXT_MK_RT_INVALID_WORK_POSITIVE_LIMIT As Short                   = 7733

    Public Const AXT_MK_RT_INVALID_TOOL_NO As Short                               = 7740

    Public Const AXT_MK_RT_INVALID_FREQUENCY_SIZE As Short                        = 7800
    Public Const AXT_MK_RT_INVALID_IMPULSE_COUNT As Short                         = 7801
    Public Const AXT_MK_RT_INVALID_AMPLITUDE As Short                             = 7802

    Public Const AXT_MK_RT_INVALID_INPUT_SHAPER__NONE As Short                    = 7803
    Public Const AXT_MK_RT_INVALID_INPUT_SHAPER_ENABLED As Short                  = 7804

    Public Const AXT_MK_RT_INVALID_ARRAY_SIZE As Short                            = 7805
    
    Public Const WM_USER As Short = &H400s
    Public Const WM_AXL_INTERRUPT As Integer = (WM_USER + 1001)

    Public Const NETWORK_TYPE_MIN As Short = 0
    Public Const NETWORK_TYPE_ALL As Short = NETWORK_TYPE_MIN
    Public Const NETWORK_TYPE_RTEX As Short = 1
    Public Const NETWORK_TYPE_MLII As Short = 2
    Public Const NETWORK_TYPE_MLIII As Short = 3
    Public Const NETWORK_TYPE_SIIIH As Short = 4
    Public Const NETWORK_TYPE_ECAT As Short = 5
    Public Const NETWORK_TYPE_MAX As Short = NETWORK_TYPE_ECAT

    Public Const LEVEL_NONE As Short = 0
    Public Const LEVEL_ERROR As Short = 1
    Public Const LEVEL_RUNSTOP As Short = 2
    Public Const LEVEL_FUNCTION As Short = 3
    
    Public Const STATUS_NOTEXIST As Short = 0
    Public Const STATUS_EXIST As Short = 1
    
    Public Const DISABLE As Short = 0
    Public Const ENABLE As Short = 1
    
    Public Const DISABLE_MODE As Short = 0
    Public Const NORMAL_MODE As Short = 1
    Public Const TIMER_MODE As Short = 2
    Public Const EXTERNAL_MODE As Short = 3
    
    Public Const NEW_DATA_KEEP As Short = 0
    Public Const CURR_DATA_KEEP As Short = 1
    
    Public Const DATA_EMPTY As Short = &H1s
    Public Const DATA_MANY As Short = &H2s
    Public Const DATA_SMALL As Short = &H4s
    Public Const DATA_FULL As Short = &H8s
    
    Public Const ADC_DONE As Short = &H0s
    Public Const SCAN_END As Short = &H1s
    Public Const FIFO_HALF_FULL As Short = &H2s
    Public Const NO_SIGNAL As Short = &H3s
    
    Public Const AIO_EVENT_DATA_RESET As Short = &H0s
    Public Const AIO_EVENT_DATA_UPPER As Short = &H1s
    Public Const AIO_EVENT_DATA_LOWER As Short = &H2s
    Public Const AIO_EVENT_DATA_FULL As Short = &H3s
    Public Const AIO_EVENT_DATA_EMPTY As Short = &H4s
    
    ' AI Module H/W FIFO Status Define
    Public Const FIFO_DATA_EXIST As Short = 0
    Public Const FIFO_DATA_EMPTY As Short = 1
    Public Const FIFO_DATA_HALF As Short = 2
    Public Const FIFO_DATA_FULL As Short = 6
    ' AI Module Conversion Status Define
    Public Const EXTERNAL_DATA_DONE As Short = 0
    Public Const EXTERNAL_DATA_FINE As Short = 1
    Public Const EXTERNAL_DATA_HALF As Short = 2
    Public Const EXTERNAL_DATA_FULL As Short = 3
    Public Const EXTERNAL_COMPLETE As Short = 4
    
    Public Const DOWN_EDGE As Short = 0
    Public Const UP_EDGE As Short = 1
    
    Public Const OFF_STATE As Short = 0
    Public Const ON_STATE As Short = 1
    
    Public Const EMERGENCY_STOP As Short = 0
    Public Const SLOWDOWN_STOP As Short = 1
    
    Public Const SIGNAL_DOWN_EDGE As Short = 0
    Public Const SIGNAL_UP_EDGE As Short = 1
    Public Const SIGNAL_LOW_LEVEL As Short = 2
    Public Const SIGNAL_HIGH_LEVEL As Short = 3

    Public Const COMMAND As Short = 0
    Public Const ACTUAL As Short = 1
    
    Public Const PERIOD_MODE As Short = 0
    Public Const ABS_POS_MODE As Short = 1
    
    Public Const LOW As Short = 0
    Public Const HIGH As Short = 1
    Public Const UNUSED As Short = 2
    Public Const USED As Short = 3

    Public Const POS_ABS_MODE As Short       = 0
    Public Const POS_REL_MODE As Short       = 1
    Public Const POS_ABS_LONG_MODE As Short  = 2
    Public Const POS_ABS_SHORT_MODE As Short = 3

    Public Const ENCODER_TYPE_INCREMENTAL As Short = 0
    Public Const ENCODER_TYPE_ABSOLUTE As Short = 1
    Public Const ENCODER_TYPE_NONE As Short = 2
    
    Public Const SYM_TRAPEZOIDE_MODE As Short = 0
    Public Const ASYM_TRAPEZOIDE_MODE As Short = 1
    Public Const QUASI_S_CURVE_MODE As Short = 2
    Public Const SYM_S_CURVE_MODE As Short = 3
    Public Const ASYM_S_CURVE_MODE As Short = 4
    Public Const SYM_TRAP_M3_SW_MODE As Short = 5    'ML-3 Only, Support Velocity profile
    Public Const ASYM_TRAP_M3_SW_MODE As Short = 6   'ML-3 Only, Support Velocity profile
    Public Const SYM_S_M3_SW_MODE As Short = 7       'ML-3 Only, Support Velocity profile
    Public Const ASYM_S_M3_SW_MODE As Short = 8      'ML-3 Only, Support Velocity profile
    
    Public Const INACTIVE As Short = 0
    Public Const ACTIVE As Short = 1
    
    Public Const HOME_RESERVED As Short = &H0S        
    Public Const HOME_SUCCESS As Short = &H1S
    Public Const HOME_SEARCHING As Short = &H2S
    Public Const HOME_ERR_GNT_RANGE As Short = &H10S
    Public Const HOME_ERR_USER_BREAK As Short = &H11S
    Public Const HOME_ERR_VELOCITY As Short = &H12S
    Public Const HOME_ERR_AMP_FAULT As Short = &H13S
    Public Const HOME_ERR_NEG_LIMIT As Short = &H14S
    Public Const HOME_ERR_POS_LIMIT As Short = &H15S
    Public Const HOME_ERR_NOT_DETECT As Short = &H16S
    Public Const HOME_ERR_SETTING As Short = &H17S
    Public Const HOME_ERR_SERVO_OFF As Short = &H18S
    Public Const HOME_ERR_TIMEOUT As Short = &H20S
    Public Const HOME_ERR_FUNCALL As Short = &H30S
    Public Const HOME_ERR_HOME_METHOD As Short = &H31S
    Public Const HOME_ERR_COUPLING As Short = &H40S
    Public Const HOME_ERR_UNKNOWN As Short = &HFFS
    
    Public Const UIO_INP0 As Short = 0
    Public Const UIO_INP1 As Short = 1
    Public Const UIO_INP2 As Short = 2
    Public Const UIO_INP3 As Short = 3
    Public Const UIO_INP4 As Short = 4
    Public Const UIO_INP5 As Short = 5
    
    Public Const UIO_OUT0 As Short = 0
    Public Const UIO_OUT1 As Short = 1
    Public Const UIO_OUT2 As Short = 2
    Public Const UIO_OUT3 As Short = 3
    Public Const UIO_OUT4 As Short = 4
    Public Const UIO_OUT5 As Short = 5
    
    Public Const AutoDetect As Short = 0
    Public Const RestPulse As Short = 1
    
    'Pulse Output Method
    Public Const OneHighLowHigh As Short = &H0s                                 '1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
    Public Const OneHighHighLow As Short = &H1s                                 '1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
    Public Const OneLowLowHigh As Short = &H2s                                  '1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
    Public Const OneLowHighLow As Short = &H3s                                  '1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
    Public Const TwoCcwCwHigh As Short = &H4s                                   '2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
    Public Const TwoCcwCwLow As Short = &H5s                                    '2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
    Public Const TwoCwCcwHigh As Short = &H6s                                   '2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
    Public Const TwoCwCcwLow As Short = &H7s                                    '2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
    Public Const TwoPhase As Short = &H8s                                       '2 phase (90'phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
    Public Const TwoPhaseReverse As Short = &H9s                                '2 phase(90' phase difference),  PULSE lead DIR(CCW: Forward direction), PULSE lag DIR(CW: Reverse direction)
    
    'Mode2 Data   External Counter Input    
    Public Const ObverseUpDownMode As Short = &H0s                              'Forward direction Up/Down
    Public Const ObverseSqr1Mode As Short = &H1s                                'Forward direction 1 multiplication
    Public Const ObverseSqr2Mode As Short = &H2s                                'Forward direction 2 multiplication
    Public Const ObverseSqr4Mode As Short = &H3s                                'Forward direction 4 multiplication
    Public Const ReverseUpDownMode As Short = &H4s                              'Reverse direction Up/Down
    Public Const ReverseSqr1Mode As Short = &H5s                                'Reverse direction 1 multiplication
    Public Const ReverseSqr2Mode As Short = &H6s                                'Reverse direction 2 multiplication
    Public Const ReverseSqr4Mode As Short = &H7s                                'Reverse direction 4 multiplication
    
    Public Const UNIT_SEC2 As Short = &H0s                                      'unit/sec2
    Public Const SEC As Short = &H1s                                            'sec
    
    Public Const DIR_CCW As Short = &H0s                                        'Counterclockwise direction
    Public Const DIR_CW As Short = &H1s                                         'Clockwise direction
    
    Public Const SHORT_DISTANCE As Short = &H0s                                 'Short distance circular movement
    Public Const LONG_DISTANCE As Short = &H1s                                  'Lone distance circular movement
    
    Public Const POSITION_LIMIT As Short = &H0S                                 'Operate within full range
    Public Const POSITION_BOUND As Short = &H1S                                 'Position range cyclic type
    
    Public Const INTERPOLATION_AXIS2 As Short = &H0s                            'When 2 axis is used for interpolation
    Public Const INTERPOLATION_AXIS3 As Short = &H1s                            'When 3 axis is used for interpolation
    Public Const INTERPOLATION_AXIS4 As Short = &H2s                            'When 4 axis is used for interpolation
    
    Public Const CONTI_NODE_VELOCITY As Short = &H0s                            'Velocity assigned interpolation mode
    Public Const CONTI_NODE_MANUAL As Short = &H1s                              'Node acceleration and deceleration interpolation mode
    Public Const CONTI_NODE_AUTO As Short = &H2s                                'Automatic acceleration and deceleration interpolation mode
    
    Public Const PosEndLimit As Short = &H0s                                    '+Elm(End limit) + direction limit sensor signal
    Public Const NegEndLimit As Short = &H1s                                    '-Elm(End limit) - direction limit sensor signal
    Public Const PosSloLimit As Short = &H2s                                    '+Slm(Decelerate limit) signal - Not-used
    Public Const NegSloLimit As Short = &H3s                                    '-Slm(Decelerate limit) signal - Not-used
    Public Const HomeSensor As Short = &H4s                                     'IN0(ORG)  home sensor signal
    Public Const EncodZPhase As Short = &H5s                                    'IN1(Z phase)  Encoder Z phase signal
    Public Const UniInput02 As Short = &H6s                                     'IN2(universal) universal input number 2 signal
    Public Const UniInput03 As Short = &H7s                                     'IN3(universal) universal input number 3 signal
    Public Const UniInput04 As Short = &H8S                                     'IN4
    Public Const UniInput05 As Short = &H9S                                     'IN5
    Public Const TorqueLimit As Short = &H10S                                   'Motor Torque Limit
    Public Const HomingMethod As Short = &H64S                                  'Homing Method Base
    Public Const HomingMethod_01 As Short = &H65S                               'Homing Method Start(90 ~ 137)
    Public Const HomingMethod_37 As Short = &H89S                               'Homing Method Start(90 ~ 137)

    Public Const END_LIMIT As Short = &H10S                                     'End limit +/-
    Public Const INP_ALARM As Short = &H11S                                     'Inposition/Alarm 
    Public Const UIN_00_01 As Short = &H12S                                     'Home/Z-Phase 
    Public Const UIN_02_04 As Short = &H13S                                     'UIN 2, 3, 4 
    
    Public Const MPG_DIFF_ONE_PHASE As Short = &H0s                             'MPG input method One Phase
    Public Const MPG_DIFF_TWO_PHASE_1X As Short = &H1s                          'MPG input method TwoPhase1
    Public Const MPG_DIFF_TWO_PHASE_2X As Short = &H2s                          'MPG input method TwoPhase2
    Public Const MPG_DIFF_TWO_PHASE_4X As Short = &H3s                          'MPG input method TwoPhase4
    Public Const MPG_LEVEL_ONE_PHASE As Short = &H4s                            'MPG input method Level One Phase
    Public Const MPG_LEVEL_TWO_PHASE_1X As Short = &H5s                         'MPG input method Level Two Phase1
    Public Const MPG_LEVEL_TWO_PHASE_2X As Short = &H6s                         'MPG input method Level Two Phase2
    Public Const MPG_LEVEL_TWO_PHASE_4X As Short = &H7s                         'MPG input method Level Two Phase4
    
    Public Const SENSOR_METHOD1 As Short = &H0s                                 'General drive
    Public Const SENSOR_METHOD2 As Short = &H1s                                 'Slow speed drive before sensor signal detection. General drive after signal detection
    Public Const SENSOR_METHOD3 As Short = &H2s                                 'Slow speed drive
    
    Public Const CRC_SELECT1 As Short = &H0s                                    'No use of position clear, no use of remaining pulse clear
    Public Const CRC_SELECT2 As Short = &H1s                                    'Use of position clear, no use of remaining pulse clear
    Public Const CRC_SELECT3 As Short = &H2s                                    'No use of position clear, use of remaining pulse clear
    Public Const CRC_SELECT4 As Short = &H3s                                    'Use of position clear, use of remaining pulse clear
    
    'Detect Destination Signal   
    Public Const PElmNegativeEdge As Short = &H0s                               '+Elm(End limit) falling edge
    Public Const NElmNegativeEdge As Short = &H1s                               '-Elm(End limit) falling edge
    Public Const PSlmNegativeEdge As Short = &H2s                               '+Slm(Slowdown limit) falling edge
    Public Const NSlmNegativeEdge As Short = &H3s                               '-Slm(Slowdown limit) falling edge
    Public Const In0DownEdge As Short = &H4s                                    'IN0(ORG) falling edge
    Public Const In1DownEdge As Short = &H5s                                    'IN1(Z phase) falling edge
    Public Const In2DownEdge As Short = &H6s                                    'IN2(universal) falling edge
    Public Const In3DownEdge As Short = &H7s                                    'IN3(universal) falling edge
    Public Const PElmPositiveEdge As Short = &H8s                               '+Elm(End limit) rising edge
    Public Const NElmPositiveEdge As Short = &H9s                               '-Elm(End limit) rising edge
    Public Const PSlmPositiveEdge As Short = &HAs                               '+Slm(Slowdown limit) rising edge
    Public Const NSlmPositiveEdge As Short = &HBs                               '-Slm(Slowdown limit) rising edge
    Public Const In0UpEdge As Short = &HCs                                      'IN0(ORG) rising edge
    Public Const In1UpEdge As Short = &HDs                                      'IN1(Z phase) rising edge
    Public Const In2UpEdge As Short = &HEs                                      'IN2(universal) rising edge
    Public Const In3UpEdge As Short = &HFs                                      'IN3(universal) rising edge
    
    'IP End status : 0x0000, Normal shutdown
    Public Const IPEND_STATUS_SLM As Short = &H1s                               'Bit 0, exit by limit decelerate stop signal input
    Public Const IPEND_STATUS_ELM As Short = &H2s                               'Bit 1, exit by limit emergency stop signal input
    Public Const IPEND_STATUS_SSTOP_SIGNAL As Short = &H4s                      'Bit 2, exit by decelerate stop signal input
    Public Const IPEND_STATUS_ESTOP_SIGNAL As Short = &H8s                      'Bit 3, exit by emergency stop signal input
    Public Const IPEND_STATUS_SSTOP_COMMAND As Short = &H10s                    'Bit 4, exit by decelerate stop command
    Public Const IPEND_STATUS_ESTOP_COMMAND As Short = &H20s                    'Bit 5, exit by emergency stop command
    Public Const IPEND_STATUS_ALARM_SIGNAL As Short = &H40s                     'Bit 6, exit by Alarm signal input
    Public Const IPEND_STATUS_DATA_ERROR As Short = &H80s                       'Bit 7, exit by data setting error
    Public Const IPEND_STATUS_DEVIATION_ERROR As Short = &H100s                 'Bit 8, exit by deviation error
    Public Const IPEND_STATUS_ORIGIN_DETECT As Short = &H200s                   'Bit 9, exit by home search
    Public Const IPEND_STATUS_SIGNAL_DETECT As Short = &H400s                   'Bit 10, exit by signal search(Signal search-1/2 drive exit)
    Public Const IPEND_STATUS_PRESET_PULSE_DRIVE As Short = &H800s              'Bit 11, Preset pulse drive exit
    Public Const IPEND_STATUS_SENSOR_PULSE_DRIVE As Short = &H1000s             'Bit 12, Sensor pulse drive exit
    Public Const IPEND_STATUS_LIMIT As Short = &H2000s                          'Bit 13, exit by Limit complete stop
    Public Const IPEND_STATUS_SOFTLIMIT As Short = &H4000s                      'Bit 14, exit by Soft limit
    Public Const IPEND_STATUS_INTERPOLATION_DRIVE As Short = &H8000s            'Bit 15, Interpolation drive exit
    
    'FS Drive status    
    Public Const IPDRIVE_STATUS_BUSY As Short = &H1s                            'Bit 0, BUSY (in DRIVE)
    Public Const IPDRIVE_STATUS_DOWN As Short = &H2s                            'Bit 1, DOWN(in deceleration DRIVE)
    Public Const IPDRIVE_STATUS_CONST As Short = &H4s                           'Bit 2, CONST(in constant speed DRIVE)
    Public Const IPDRIVE_STATUS_UP As Short = &H8s                              'Bit 3, UP(in acceleration DRIVE)
    Public Const IPDRIVE_STATUS_ICL As Short = &H10s                            'Bit 4, ICL(ICM < INCNT)
    Public Const IPDRIVE_STATUS_ICG As Short = &H20s                            'Bit 5, ICG(ICM < INCNT)
    Public Const IPDRIVE_STATUS_ECL As Short = &H40s                            'Bit 6, ECL(ECM > EXCNT)
    Public Const IPDRIVE_STATUS_ECG As Short = &H80s                            'Bit 7, ECG(ECM < EXCNT)
    Public Const IPDRIVE_STATUS_DRIVE_DIRECTION As Short = &H100s               'Bit 8, drive direction signal (0=CW/1=CCW)
    Public Const IPDRIVE_STATUS_COMMAND_BUSY As Short = &H200s                  'Bit 9, In execution of command
    Public Const IPDRIVE_STATUS_PRESET_DRIVING As Short = &H400s                'Bit 10, In drive of a specific pulse number
    Public Const IPDRIVE_STATUS_CONTINUOUS_DRIVING As Short = &H800s            'Bit 11, In continuous drive
    Public Const IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING As Short = &H1000s        'Bit 12, In signal search drive
    Public Const IPDRIVE_STATUS_ORG_SEARCH_DRIVING As Short = &H2000s           'Bit 13, In home search drive
    Public Const IPDRIVE_STATUS_MPG_DRIVING As Short = &H4000s                  'Bit 14, In MPG drive
    Public Const IPDRIVE_STATUS_SENSOR_DRIVING As Short = &H8000s               'Bit 15, In sensor position drive
    Public Const IPDRIVE_STATUS_L_C_INTERPOLATION As Integer = &H10000          'Bit 16, In straight/circular interpolation drive
    Public Const IPDRIVE_STATUS_PATTERN_INTERPOLATION As Integer = &H20000      'Bit 17, In pattern interpolation drive
    Public Const IPDRIVE_STATUS_INTERRUPT_BANK1 As Integer = &H40000            'Bit 18, Interrupt occurrence in BANK1
    Public Const IPDRIVE_STATUS_INTERRUPT_BANK2 As Integer = &H80000            'Bit 19, Interrupt occurrence in BANK2
    
    'IP Interrupt MASK setting    
    Public Const IPINTBANK1_DONTUSE As Short = &H0s                             'INTERRUT DISABLED.
    Public Const IPINTBANK1_DRIVE_END As Short = &H1s                           'Bit 0, Drive end(default value : 1).
    Public Const IPINTBANK1_ICG As Short = &H2s                                 'Bit 1, INCNT is greater than INCNTCMP.
    Public Const IPINTBANK1_ICE As Short = &H4s                                 'Bit 2, INCNT is equal with INCNTCMP.
    Public Const IPINTBANK1_ICL As Short = &H8s                                 'Bit 3, INCNT is less than INCNTCMP.
    Public Const IPINTBANK1_ECG As Short = &H10s                                'Bit 4, EXCNT is greater than EXCNTCMP.
    Public Const IPINTBANK1_ECE As Short = &H20s                                'Bit 5, EXCNT is equal with EXCNTCMP.
    Public Const IPINTBANK1_ECL As Short = &H40s                                'Bit 6, EXCNT is less than EXCNTCMP.
    Public Const IPINTBANK1_SCRQEMPTY As Short = &H80s                          'Bit 7, Script control queue is empty.
    Public Const IPINTBANK1_CAPRQEMPTY As Short = &H100s                        'Bit 8, Caption result data queue is empty.
    Public Const IPINTBANK1_SCRREG1EXE As Short = &H200s                        'Bit 9, Script control register-1 command is executed.
    Public Const IPINTBANK1_SCRREG2EXE As Short = &H400s                        'Bit 10, Script control register-2 command is executed.
    Public Const IPINTBANK1_SCRREG3EXE As Short = &H800s                        'Bit 11, Script control register-3 command is executed.
    Public Const IPINTBANK1_CAPREG1EXE As Short = &H1000s                       'Bit 12, Caption control register-1 command is executed.
    Public Const IPINTBANK1_CAPREG2EXE As Short = &H2000s                       'Bit 13, Caption control register-2 command is executed.
    Public Const IPINTBANK1_CAPREG3EXE As Short = &H4000s                       'Bit 14, Caption control register-3 command is executed.
    Public Const IPINTBANK1_INTGGENCMD As Short = &H8000s                       'Bit 15, Interrupt generation command is executed(0xFF)
    Public Const IPINTBANK1_DOWN As Integer = &H10000                           'Bit 16, At starting point for deceleration drive.
    Public Const IPINTBANK1_CONT As Integer = &H20000                           'Bit 17, At starting point for constant speed drive.
    Public Const IPINTBANK1_UP As Integer = &H40000                             'Bit 18, At starting point for acceleration drive.
    Public Const IPINTBANK1_SIGNALDETECTED As Integer = &H80000                 'Bit 19, Signal assigned in MODE1 is detected.
    Public Const IPINTBANK1_SP23E As Integer = &H100000                         'Bit 20, Current speed is equal with rate change point RCP23.
    Public Const IPINTBANK1_SP12E As Integer = &H200000                         'Bit 21, Current speed is equal with rate change point RCP12.
    Public Const IPINTBANK1_SPE As Integer = &H400000                           'Bit 22, Current speed is equal with speed comparison data(SPDCMP).
    Public Const IPINTBANK1_INCEICM As Integer = &H800000                       'Bit 23, INTCNT(1'st counter) is equal with ICM(1'st count minus limit data)
    Public Const IPINTBANK1_SCRQEXE As Integer = &H1000000                      'Bit 24, Script queue command is executed When SCRCONQ's 30 bit is '1'.
    Public Const IPINTBANK1_CAPQEXE As Integer = &H2000000                      'Bit 25, Caption queue command is executed When CAPCONQ's 30 bit is '1'.
    Public Const IPINTBANK1_SLM As Integer = &H4000000                          'Bit 26, NSLM/PSLM input signal is activated.
    Public Const IPINTBANK1_ELM As Integer = &H8000000                          'Bit 27, NELM/PELM input signal is activated.
    Public Const IPINTBANK1_USERDEFINE1 As Integer = &H10000000                 'Bit 28, Selectable interrupt source 0(refer "0xFE" command).
    Public Const IPINTBANK1_USERDEFINE2 As Integer = &H20000000                 'Bit 29, Selectable interrupt source 1(refer "0xFE" command).
    Public Const IPINTBANK1_USERDEFINE3 As Integer = &H40000000                 'Bit 30, Selectable interrupt source 2(refer "0xFE" command).
    Public Const IPINTBANK1_USERDEFINE4 As Integer = &H80000000                 'Bit 31, Selectable interrupt source 3(refer "0xFE" command).
    
    Public Const IPINTBANK2_DONTUSE As Short = &H0s                             'INTERRUT DISABLED.
    Public Const IPINTBANK2_L_C_INP_Q_EMPTY As Short = &H1s                     'Bit 0, Linear/Circular interpolation parameter queue is empty.
    Public Const IPINTBANK2_P_INP_Q_EMPTY As Short = &H2s                       'Bit 1, Bit pattern interpolation queue is empty.
    Public Const IPINTBANK2_ALARM_ERROR As Short = &H4s                         'Bit 2, Alarm input signal is activated.
    Public Const IPINTBANK2_INPOSITION As Short = &H8s                          'Bit 3, Inposition input signal is activated.
    Public Const IPINTBANK2_MARK_SIGNAL_HIGH As Short = &H10s                   'Bit 4, Mark input signal is activated.
    Public Const IPINTBANK2_SSTOP_SIGNAL As Short = &H20s                       'Bit 5, SSTOP input signal is activated.
    Public Const IPINTBANK2_ESTOP_SIGNAL As Short = &H40s                       'Bit 6, ESTOP input signal is activated.
    Public Const IPINTBANK2_SYNC_ACTIVATED As Short = &H80s                     'Bit 7, SYNC input signal is activated.
    Public Const IPINTBANK2_TRIGGER_ENABLE As Short = &H100s                    'Bit 8, Trigger output is activated.
    Public Const IPINTBANK2_EXCNTCLR As Short = &H200s                          'Bit 9, External(2'nd) counter is cleard by EXCNTCLR setting.
    Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT0 As Short = &H400s            'Bit 10, ALU1's compare result bit 0 is activated.
    Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT1 As Short = &H800s            'Bit 11, ALU1's compare result bit 1 is activated.
    Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT2 As Short = &H1000s           'Bit 12, ALU1's compare result bit 2 is activated.
    Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT3 As Short = &H2000s           'Bit 13, ALU1's compare result bit 3 is activated.
    Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT4 As Short = &H4000s           'Bit 14, ALU1's compare result bit 4 is activated.
    Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT0 As Short = &H8000s           'Bit 15, ALU2's compare result bit 0 is activated.
    Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT1 As Integer = &H10000         'Bit 16, ALU2's compare result bit 1 is activated.
    Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT2 As Integer = &H20000         'Bit 17, ALU2's compare result bit 2 is activated.
    Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT3 As Integer = &H40000         'Bit 18, ALU2's compare result bit 3 is activated.
    Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT4 As Integer = &H80000         'Bit 19, ALU2's compare result bit 4 is activated.
    Public Const IPINTBANK2_L_C_INP_Q_LESS_4 As Integer = &H100000              'Bit 20, Linear/Circular interpolation parameter queue is less than 4.
    Public Const IPINTBANK2_P_INP_Q_LESS_4 As Integer = &H200000                'Bit 21, Pattern interpolation parameter queue is less than 4.
    Public Const IPINTBANK2_XSYNC_ACTIVATED As Integer = &H400000               'Bit 22, X axis sync input signal is activated.
    Public Const IPINTBANK2_YSYNC_ACTIVATED As Integer = &H800000               'Bit 23, Y axis sync input siangl is activated.
    Public Const IPINTBANK2_P_INP_END_BY_END_PATTERN As Integer = &H1000000     'Bit 24, Bit pattern interpolation is terminated by end pattern.
    'IPINTBANK2_              = 0x02000000,   // Bit 25, Don't care.
    'IPINTBANK2_              = 0x04000000,   // Bit 26, Don't care.
    'IPINTBANK2_              = 0x08000000,   // Bit 27, Don't care.
    'IPINTBANK2_              = 0x10000000,   // Bit 28, Don't care.
    'IPINTBANK2_              = 0x20000000,   // Bit 29, Don't care.
    'IPINTBANK2_              = 0x40000000,   // Bit 30, Don't care.
    'IPINTBANK2_              = 0x80000000    // Bit 31, Don't care.
    
    'IP Drive status
    Public Const IPMECHANICAL_PELM_LEVEL As Short = &H1s                        'Bit 0, +Limit emergency stop signal input Level
    Public Const IPMECHANICAL_NELM_LEVEL As Short = &H2s                        'Bit 1, -Limit emergency stop signal input Level
    Public Const IPMECHANICAL_PSLM_LEVEL As Short = &H4s                        'Bit 2, +limit decelerate stop signal input Level
    Public Const IPMECHANICAL_NSLM_LEVEL As Short = &H8s                        'Bit 3, -limit decelerate stop signal input Level
    Public Const IPMECHANICAL_ALARM_LEVEL As Short = &H10s                      'Bit 4, Alarm signal input Level
    Public Const IPMECHANICAL_INP_LEVEL As Short = &H20s                        'Bit 5, InPos signal input Level
    Public Const IPMECHANICAL_ENC_DOWN_LEVEL As Short = &H40s                   'Bit 6, encoder DOWN(B phase) signal input Level
    Public Const IPMECHANICAL_ENC_UP_LEVEL As Short = &H80s                     'Bit 7, encoder UP(A phase) signal input Level
    Public Const IPMECHANICAL_EXMP_LEVEL As Short = &H100s                      'Bit 8, EXMP signal input Level
    Public Const IPMECHANICAL_EXPP_LEVEL As Short = &H200s                      'Bit 9, EXPP signal input Level
    Public Const IPMECHANICAL_MARK_LEVEL As Short = &H400s                      'Bit 10, MARK# signal input Level
    Public Const IPMECHANICAL_SSTOP_LEVEL As Short = &H800s                     'Bit 11, SSTOP signal input Level
    Public Const IPMECHANICAL_ESTOP_LEVEL As Short = &H1000s                    'Bit 12, ESTOP signal input Level
    Public Const IPMECHANICAL_SYNC_LEVEL As Short = &H2000s                     'Bit 13, SYNC signal input Level
    Public Const IPMECHANICAL_MODE8_16_LEVEL As Short = &H4000s                 'Bit 14, MODE8_16 signal input Level
    
    'Detect Destination Signal    
    Public Const Signal_PosEndLimit As Short = &H0s                             '+Elm(End limit) + direction limit sensor signal
    Public Const Signal_NegEndLimit As Short = &H1s                             '-Elm(End limit) - direction limit sensor signal
    Public Const Signal_PosSloLimit As Short = &H2s                             '+Slm(Slow Down limit) signal - Not-used
    Public Const Signal_NegSloLimit As Short = &H3s                             '-Slm(Slow Down limit) signal - Not-used
    Public Const Signal_HomeSensor As Short = &H4s                              'IN0(ORG)  home sensor signal
    Public Const Signal_EncodZPhase As Short = &H5s                             'IN1(Z phase)  Encoder Z phase signal
    Public Const Signal_UniInput02 As Short = &H6s                              'IN2(universal) universal input number 2 signal
    Public Const Signal_UniInput03 As Short = &H7s                              'IN3(universal) universal input number 3 signal
    
    'QI Drive status
    Public Const QIMECHANICAL_PELM_LEVEL As Short = &H1s                        'Bit 0, +Limit emergency stop signal current state
    Public Const QIMECHANICAL_NELM_LEVEL As Short = &H2s                        'Bit 1, -Limit emergency stop signal current state
    Public Const QIMECHANICAL_PSLM_LEVEL As Short = &H4s                        'Bit 2, +limit decelerate stop signal current state
    Public Const QIMECHANICAL_NSLM_LEVEL As Short = &H8s                        'Bit 3, -limit decelerate stop signal current state
    Public Const QIMECHANICAL_ALARM_LEVEL As Short = &H10s                      'Bit 4, Alarm signal current state
    Public Const QIMECHANICAL_INP_LEVEL As Short = &H20s                        'Bit 5, InPos signal current state
    Public Const QIMECHANICAL_ESTOP_LEVEL As Short = &H40s                      'Bit 6, emergency stop signal(ESTOP) current state
    Public Const QIMECHANICAL_ORG_LEVEL As Short = &H80s                        'Bit 7, home signal current state
    Public Const QIMECHANICAL_ZPHASE_LEVEL As Short = &H100s                    'Bit 8, Z phase input signal current state
    Public Const QIMECHANICAL_ECUP_LEVEL As Short = &H200s                      'Bit 9, ECUP terminal signal state
    Public Const QIMECHANICAL_ECDN_LEVEL As Short = &H400s                      'Bit 10, ECDN terminal signal state
    Public Const QIMECHANICAL_EXPP_LEVEL As Short = &H800s                      'Bit 11, EXPP terminal signal state
    Public Const QIMECHANICAL_EXMP_LEVEL As Short = &H1000s                     'Bit 12, EXMP terminal signal state
    Public Const QIMECHANICAL_SQSTR1_LEVEL As Short = &H2000s                   'Bit 13, SQSTR1 terminal signal state
    Public Const QIMECHANICAL_SQSTR2_LEVEL As Short = &H4000s                   'Bit 14, SQSTR2 terminal signal state
    Public Const QIMECHANICAL_SQSTP1_LEVEL As Short = &H8000s                   'Bit 15, SQSTP1 terminal signal state
    Public Const QIMECHANICAL_SQSTP2_LEVEL As Integer = &H10000                 'Bit 16, SQSTP2 terminal signal state
    Public Const QIMECHANICAL_MODE_LEVEL As Integer = &H20000                   'Bit 17, MODE terminal signal state
    
    'QI End status : 0x0000
    Public Const QIEND_STATUS_0 As Short = &H1s                                 'Bit 0, exit by forward direction limit signal (PELM)
    Public Const QIEND_STATUS_1 As Short = &H2s                                 'Bit 1, exit by reverse direction limit signal (NELM)
    Public Const QIEND_STATUS_2 As Short = &H4s                                 'Bit 2, exit by forward direction additional limit signal (PSLM)
    Public Const QIEND_STATUS_3 As Short = &H8s                                 'Bit 3, exit by reverse direction additional limit signal (NSLM)
    Public Const QIEND_STATUS_4 As Short = &H10s                                'Bit 4, exit by forward direction soft limit emergency stop function
    Public Const QIEND_STATUS_5 As Short = &H20s                                'Bit 5, exit by reverse direction soft limit emergency stop function
    Public Const QIEND_STATUS_6 As Short = &H40s                                'Bit 6, exit by forward direction soft limit decelerate stop function
    Public Const QIEND_STATUS_7 As Short = &H80s                                'Bit 7, exit by reverse direction soft limit decelerate stop function
    Public Const QIEND_STATUS_8 As Short = &H100s                               'Bit 8, drive exit by servo alarm function
    Public Const QIEND_STATUS_9 As Short = &H200s                               'Bit 9, drive exit by emergency stop signal input
    Public Const QIEND_STATUS_10 As Short = &H400s                              'Bit 10, drive exit by emergency stop command
    Public Const QIEND_STATUS_11 As Short = &H800s                              'Bit 11, drive exit by decelerate stop command
    Public Const QIEND_STATUS_12 As Short = &H1000s                             'Bit 12, drive exit by entire axes emergency stop command
    Public Const QIEND_STATUS_13 As Short = &H2000s                             'Bit 13, drive exit by sync stop function #1(SQSTP1)
    Public Const QIEND_STATUS_14 As Short = &H4000s                             'Bit 14, drive exit by sync stop function #2(SQSTP2)
    Public Const QIEND_STATUS_15 As Short = &H8000s                             'Bit 15, encoder input (ECUP,ECDN) error occurrence
    Public Const QIEND_STATUS_16 As Integer = &H10000                           'Bit 16, MPG input (EXPP,EXMP) error occurrence
    Public Const QIEND_STATUS_17 As Integer = &H20000                           'Bit 17, exit with successful home search
    Public Const QIEND_STATUS_18 As Integer = &H40000                           'Bit 18, exit with successful signal search
    Public Const QIEND_STATUS_19 As Integer = &H80000                           'Bit 19, drive exit by interpolation data abnormality
    Public Const QIEND_STATUS_20 As Integer = &H100000                          'Bit 20, abnormal drive stop occurrence
    Public Const QIEND_STATUS_21 As Integer = &H200000                          'Bit 21, MPG function block pulse buffer overflow occurrence
    Public Const QIEND_STATUS_22 As Integer = &H400000                          'Bit 22, DON'CARE
    Public Const QIEND_STATUS_23 As Integer = &H800000                          'Bit 23, DON'CARE
    Public Const QIEND_STATUS_24 As Integer = &H1000000                         'Bit 24, DON'CARE
    Public Const QIEND_STATUS_25 As Integer = &H2000000                         'Bit 25, DON'CARE
    Public Const QIEND_STATUS_26 As Integer = &H4000000                         'Bit 26, DON'CARE
    Public Const QIEND_STATUS_27 As Integer = &H8000000                         'Bit 27, DON'CARE
    Public Const QIEND_STATUS_28 As Integer = &H10000000                        'Bit 28, current/last move drive direction
    Public Const QIEND_STATUS_29 As Integer = &H20000000                        'Bit 29, in output of remaining pulse clear
    Public Const QIEND_STATUS_30 As Integer = &H40000000                        'Bit 30, abnormal drive stop cause state
    Public Const QIEND_STATUS_31 As Integer = &H80000000                        'Bit 31, interpolation drive data error state
    
    'QI Drive status
    Public Const QIDRIVE_STATUS_0 As Short = &H1s                               'Bit 0, BUSY(in drive move)
    Public Const QIDRIVE_STATUS_1 As Short = &H2s                               'Bit 1, DOWN(in deceleration)
    Public Const QIDRIVE_STATUS_2 As Short = &H4s                               'Bit 2, CONST(in constant speed)
    Public Const QIDRIVE_STATUS_3 As Short = &H8s                               'Bit 3, UP(in acceleration)
    Public Const QIDRIVE_STATUS_4 As Short = &H10s                              'Bit 4, in move of continuous drive
    Public Const QIDRIVE_STATUS_5 As Short = &H20s                              'Bit 5, in move of assigned distance drive
    Public Const QIDRIVE_STATUS_6 As Short = &H40s                              'Bit 6, in move of MPG drive
    Public Const QIDRIVE_STATUS_7 As Short = &H80s                              'Bit 7, in move of home search drive
    Public Const QIDRIVE_STATUS_8 As Short = &H100s                             'Bit 8, in move of signal search drive
    Public Const QIDRIVE_STATUS_9 As Short = &H200s                             'Bit 9, in move of interpolation drive
    Public Const QIDRIVE_STATUS_10 As Short = &H400s                            'Bit 10, in move of Slave drive
    Public Const QIDRIVE_STATUS_11 As Short = &H800s                            'Bit 11, current move drive direction (different indication information in interpolation drive)
    Public Const QIDRIVE_STATUS_12 As Short = &H1000s                           'Bit 12, in waiting for servo position completion after pulse output
    Public Const QIDRIVE_STATUS_13 As Short = &H2000s                           'Bit 13, in move of straight line interpolation drive
    Public Const QIDRIVE_STATUS_14 As Short = &H4000s                           'Bit 14, in move of circular interpolation drive
    Public Const QIDRIVE_STATUS_15 As Short = &H8000s                           'Bit 15, in pulse output
    Public Const QIDRIVE_STATUS_16 As Integer = &H10000                         'Bit 16, drive reserved data number(start)(0-7)
    Public Const QIDRIVE_STATUS_17 As Integer = &H20000                         'Bit 17, drive reserved data number (middle)(0-7)
    Public Const QIDRIVE_STATUS_18 As Integer = &H40000                         'Bit 18, drive reserved data number (end)(0-7)
    Public Const QIDRIVE_STATUS_19 As Integer = &H80000                         'Bit 19, drive reversed Queue is cleared
    Public Const QIDRIVE_STATUS_20 As Integer = &H100000                        'Bit 20, drive reversed Queue is full
    Public Const QIDRIVE_STATUS_21 As Integer = &H200000                        'Bit 21, velocity mode of current move drive (start)
    Public Const QIDRIVE_STATUS_22 As Integer = &H400000                        'Bit 22, velocity mode of current move drive (end)
    Public Const QIDRIVE_STATUS_23 As Integer = &H800000                        'Bit 23, MPG buffer #1 Full
    Public Const QIDRIVE_STATUS_24 As Integer = &H1000000                       'Bit 24, MPG buffer #2 Full
    Public Const QIDRIVE_STATUS_25 As Integer = &H2000000                       'Bit 25, MPG buffer #3 Full
    Public Const QIDRIVE_STATUS_26 As Integer = &H4000000                       'Bit 26, MPG buffer data OverFlow
    
    'QI Interrupt MASK setting    
    Public Const QIINTBANK1_DISABLE As Short = &H0s                             'INTERRUT DISABLED.
    Public Const QIINTBANK1_0 As Short = &H1s                                   'Bit 0,  when drive set interrupt occurrence use is exit
    Public Const QIINTBANK1_1 As Short = &H2s                                   'Bit 1,  when drive is exited
    Public Const QIINTBANK1_2 As Short = &H4s                                   'Bit 2,  when drive is started
    Public Const QIINTBANK1_3 As Short = &H8s                                   'Bit 3,  counter #1 < comparator #1 event occurrence
    Public Const QIINTBANK1_4 As Short = &H10s                                  'Bit 4,  counter #1 = comparator #1 event occurrence
    Public Const QIINTBANK1_5 As Short = &H20s                                  'Bit 5,  counter #1 > comparator #1 event occurrence
    Public Const QIINTBANK1_6 As Short = &H40s                                  'Bit 6,  counter #2 < comparator #2 event occurrence
    Public Const QIINTBANK1_7 As Short = &H80s                                  'Bit 7,  counter #2 = comparator #2 event occurrence
    Public Const QIINTBANK1_8 As Short = &H100s                                 'Bit 8,  counter #2 > comparator #2 event occurrence
    Public Const QIINTBANK1_9 As Short = &H200s                                 'Bit 9,  counter #3 < comparator #3 event occurrence
    Public Const QIINTBANK1_10 As Short = &H400s                                'Bit 10, counter #3 = comparator #3 event occurrence
    Public Const QIINTBANK1_11 As Short = &H800s                                'Bit 11, counter #3 > comparator #3 event occurrence
    Public Const QIINTBANK1_12 As Short = &H1000s                               'Bit 12, counter #4 < comparator #4 event occurrence
    Public Const QIINTBANK1_13 As Short = &H2000s                               'Bit 13, counter #4 = comparator #4 event occurrence
    Public Const QIINTBANK1_14 As Short = &H4000s                               'Bit 14, counter #4 < comparator #4 event occurrence
    Public Const QIINTBANK1_15 As Short = &H8000s                               'Bit 15, counter #5 < comparator #5 event occurrence
    Public Const QIINTBANK1_16 As Integer = &H10000                             'Bit 16, counter #5 = comparator #5 event occurrence
    Public Const QIINTBANK1_17 As Integer = &H20000                             'Bit 17, counter #5 > comparator #5 event occurrence
    Public Const QIINTBANK1_18 As Integer = &H40000                             'Bit 18, timer #1 event occurrence
    Public Const QIINTBANK1_19 As Integer = &H80000                             'Bit 19, timer #2 event occurrence
    Public Const QIINTBANK1_20 As Integer = &H100000                            'Bit 20, drive reservation setting Queue is cleared
    Public Const QIINTBANK1_21 As Integer = &H200000                            'Bit 21, drive reservation setting Queue is full
    Public Const QIINTBANK1_22 As Integer = &H400000                            'Bit 22, trigger occurring distance period/absolute position Queue is cleared
    Public Const QIINTBANK1_23 As Integer = &H800000                            'Bit 23, trigger occurring distance period/absolute position Queue is full
    Public Const QIINTBANK1_24 As Integer = &H1000000                           'Bit 24, trigger signal occurrence event
    Public Const QIINTBANK1_25 As Integer = &H2000000                           'Bit 25, script #1 command reservation setting Queue is cleared
    Public Const QIINTBANK1_26 As Integer = &H4000000                           'Bit 26, script #2 command reservation setting Queue is cleared
    Public Const QIINTBANK1_27 As Integer = &H8000000                           'Bit 27, script #3 initialized with execution of command reservation setting register
    Public Const QIINTBANK1_28 As Integer = &H10000000                          'Bit 28, script #4 initialized with execution of command reservation setting register
    Public Const QIINTBANK1_29 As Integer = &H20000000                          'Bit 29, servo alarm signal is permitted
    Public Const QIINTBANK1_30 As Integer = &H40000000                          'Bit 30, |CNT1| - |CNT2| >= |CNT4| event occurrence
    Public Const QIINTBANK1_31 As Integer = &H80000000                          'Bit 31, interrupt occurrence command |INTGEN| execution
    
    Public Const QIINTBANK2_DISABLE As Short = &H0s                             'INTERRUT DISABLED.
    Public Const QIINTBANK2_0 As Short = &H1s                                   'Bit 0,  script #1 reading command result Queue is full
    Public Const QIINTBANK2_1 As Short = &H2s                                   'Bit 1,  script #2 reading command result Queue is full
    Public Const QIINTBANK2_2 As Short = &H4s                                   'Bit 2,  script #3 reading command result register is renewed with new data
    Public Const QIINTBANK2_3 As Short = &H8s                                   'Bit 3,  script #4 reading command result register is renewed with new data
    Public Const QIINTBANK2_4 As Short = &H10s                                  'Bit 4,  when reservation command of script #1 is executed, command set by interrupt occurrence is executed
    Public Const QIINTBANK2_5 As Short = &H20s                                  'Bit 5,  when reservation command of script #2 is executed, command set by interrupt occurrence is executed
    Public Const QIINTBANK2_6 As Short = &H40s                                  'Bit 6,  when reservation command of script #3 is executed, command set by interrupt occurrence is executed
    Public Const QIINTBANK2_7 As Short = &H80s                                  'Bit 7,  when reservation command of script #4 is executed, command set by interrupt occurrence is executed
    Public Const QIINTBANK2_8 As Short = &H100s                                 'Bit 8,  start drive
    Public Const QIINTBANK2_9 As Short = &H200s                                 'Bit 9,  drive using servo position determination completion(InPos) function, exit condition occurrence
    Public Const QIINTBANK2_10 As Short = &H400s                                'Bit 10, event selection #1 condition occurrence to use during event counter operation
    Public Const QIINTBANK2_11 As Short = &H800s                                'Bit 11, event selection #2 condition occurrence to use during event counter operation
    Public Const QIINTBANK2_12 As Short = &H1000s                               'Bit 12, SQSTR1 signal is permitted
    Public Const QIINTBANK2_13 As Short = &H2000s                               'Bit 13, SQSTR2 signal is permitted
    Public Const QIINTBANK2_14 As Short = &H4000s                               'Bit 14, UIO0 terminal signal is changed to '1'
    Public Const QIINTBANK2_15 As Short = &H8000s                               'Bit 15, UIO1 terminal signal is changed to '1'
    Public Const QIINTBANK2_16 As Integer = &H10000                             'Bit 16, UIO2 terminal signal is changed to '1'
    Public Const QIINTBANK2_17 As Integer = &H20000                             'Bit 17, UIO3 terminal signal is changed to '1'
    Public Const QIINTBANK2_18 As Integer = &H40000                             'Bit 18, UIO4 terminal signal is changed to '1'
    Public Const QIINTBANK2_19 As Integer = &H80000                             'Bit 19, UIO5 terminal signal is changed to '1'
    Public Const QIINTBANK2_20 As Integer = &H100000                            'Bit 20, UIO6 terminal signal is changed to '1'
    Public Const QIINTBANK2_21 As Integer = &H200000                            'Bit 21, UIO7 terminal signal is changed to '1'
    Public Const QIINTBANK2_22 As Integer = &H400000                            'Bit 22, UIO8 terminal signal is changed to '1'
    Public Const QIINTBANK2_23 As Integer = &H800000                            'Bit 23, UIO9 terminal signal is changed to '1'
    Public Const QIINTBANK2_24 As Integer = &H1000000                           'Bit 24, UIO10 terminal signal is changed to '1'
    Public Const QIINTBANK2_25 As Integer = &H2000000                           'Bit 25, UIO11 terminal signal is changed to '1'
    Public Const QIINTBANK2_26 As Integer = &H4000000                           'Bit 26, error stop condition (LMT, ESTOP, STOP, ESTOP, CMD, ALARM) occurrence
    Public Const QIINTBANK2_27 As Integer = &H8000000                           'Bit 27, data setting error is occurred during interpolation
    Public Const QIINTBANK2_28 As Integer = &H10000000                          'Bit 28, Don't Care
    Public Const QIINTBANK2_29 As Integer = &H20000000                          'Bit 29, limit signal (PELM, NELM) is inputted
    Public Const QIINTBANK2_30 As Integer = &H40000000                          'Bit 30, additional limit signal (PSLM, NSLM) is inputted
    Public Const QIINTBANK2_31 As Integer = &H80000000                          'Bit 31, emergency stop signal (ESTOP) is input
    
    'Network Status
    Public Const NET_STATUS_DISCONNECTED As Short = 1
    Public Const NET_STATUS_LOCK_MISMATCH As Short = 5
    Public Const NET_STATUS_CONNECTED As Short = 6
    
    ' Define Motion Information
    Structure PMOTION_INFO
        Public dCmdPos As Double             ' Command position[0x01]
        Public dActPos As Double             ' Encoder position[0x02]
        Public dwMechSig As Long             ' Mechanical Signal[0x04]
        Public dwDrvStat As Long             ' Driver Status[0x08]
        Public dwInput As Long               ' Universal Signal Input[0x10]
        Public dwOutput As Long              ' Universal Signal Output[0x10]
        Public dwMask As Long                ' Read settings Mask Ex) 0x1F, read all information
    End Structure
    
    ' Motion(QI) Override Condition
    Public Const OVERRIDE_POS_START As Short = 0
    Public Const OVERRIDE_POS_END As Short = 1
    Public Const OVERRIDE_POS_AUTO As Short = 2  
    ' Motion(QI) Profile Priority
    Public Const PRIORITY_VELOCITY As Short = 0
    Public Const PRIORITY_ACCELTIME As Short = 1
    ' Function Return Type Define
    Public Const FUNC_RETURN_IMMEDIATE As Short = 0
    Public Const FUNC_RETURN_BLOCKING As Short = 1
    Public Const FUNC_RETURN_NON_BLOCKING As Short = 2

    Public Const BACKLASH_DIR_P As Short = 0
    Public Const BACKLASH_DIR_N As Short = 1
    Public Const BACKLASH_DIR_U As Short = 2

    ' Max alarm history count
    Public Const MAX_SERVO_ALARM_HISTORY As Short = 15
    
    ' Mechatrolink III
    Public Const COM_CONNECT As Short = 0
    Public Const COM_DISCONNECT As Short = 1
    Public Const COM_OFFLINE As Short = 2

    Public Enum MONITOR_SELECT_INFORMATION
        _MONI_APOS_ = 0        ' feedback position  : current position of the motor
        _MONI_CPOS_ = 1        ' command position   : command position after acceleration/deceleration filter
        _MONI_PERR_ = 2        ' position error     : Position error of the control loop
        _MONI_LPOS1_ = 3       ' latched position 1 : motor position 1 latched by the latch signal
        _MONI_LPOS2_ = 4       ' latched position 2 : motor position 2 latched by the latch signal
        _MONI_FSPD_ = 5        ' feedback speed     : current speed of the motor
        _MONI_CSPD_ = 6        ' reference speed    : command speed of the motor
        _MONI_TRQ_ = 7         ' torque(force) reference : command torque(force) of the motor
        _MONI_ALARM_ = 8       ' detailed information on the current alarm : current alarm/warning (2-byte data, higher 2 bytes fixed as 0x0000)
        _MONI_MPOS_ = 9        ' command position(optional) : the details of the monitor data are specified in the product specifications. example : internal command position of the control loop
        _MONI_RES1_ = 10       ' reserved
        _MONI_RES2_ = 11       ' reserved
        _MONI_CMN1_ = 12       ' common monitor 1 : selects the monitor data specified at common parameter 89.(for the contents of the monitor data, refer to common parameter 89)
        _MONI_CMN2_ = 13       ' common monitor 2 : selects the monitor data specified at common parameter 8A.(for the contents of the monitor data, refer to common parameter 8A)
        _MONI_OMN1_ = 14       ' optional monitor 1 : selects the monitor data specified by parameter.(the contents of the monitor data depend on the product specifications)
        _MONI_OMN2_ = 15       ' optional monitor 2 : selects the monitor data specified by parameter.(the contents of the monitor data depend on the product specifications)
    End Enum

    ' Counter Module Define
    Public Const F_50M_CLK As Integer = 50000000

    Public Const CnCommand As Short = &H10S
    Public Const CnData1 As Short = &H12S
    Public Const CnData2 As Short = &H14S
    Public Const CnData3 As Short = &H16S
    Public Const CnData4 As Short = &H18S
    Public Const CnData12 As Short = &H44S
    Public Const CnData34 As Short = &H46S

    Public Const CnRamAddr1 As Short = &H28S
    Public Const CnRamAddr2 As Short = &H2AS
    Public Const CnRamAddr3 As Short = &H2CS
    Public Const CnRamAddrx1 As Short = &H48S
    Public Const CnRamAddr23 As Short = &H4AS

    Public Const CnAbPhase As Short = 0
    Public Const CnZPhase As Short = 1

    Public Const CnUpDownMode As Short = 0
    Public Const CnSqr1Mode As Short = 1
    Public Const CnSqr2Mode As Short = 2
    Public Const CnSqr4Mode As Short = 3

    ' CH-1 Group Register
    Public Const CnCh1CounterRead As Short = &H10S                       ' CH1 COUNTER READ, 24BIT
    Public Const CnCh1CounterWrite As Short = &H90S                      ' CH1 COUNTER WRITE
    Public Const CnCh1CounterModeRead As Short = &H11S                   ' CH1 COUNTER MODE READ, 8BIT
    Public Const CnCh1CounterModeWrite As Short = &H91S                  ' CH1 COUNTER MODE WRITE
    Public Const CnCh1TriggerRegionLowerDataRead As Short = &H12S        ' CH1 TRIGGER REGION LOWER DATA READ, 24BIT
    Public Const CnCh1TriggerRegionLowerDataWrite As Short = &H92S       ' CH1 TRIGGER REGION LOWER DATA WRITE
    Public Const CnCh1TriggerRegionUpperDataRead As Short = &H13S        ' CH1 TRIGGER REGION UPPER DATA READ, 24BIT
    Public Const CnCh1TriggerRegionUpperDataWrite As Short = &H93S       ' CH1 TRIGGER REGION UPPER DATA WRITE
    Public Const CnCh1TriggerPeriodRead As Short = &H14S                 ' CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
    Public Const CnCh1TriggerPeriodWrite As Short = &H94S                ' CH1 TRIGGER PERIOD WRITE
    Public Const CnCh1TriggerPulseWidthRead As Short = &H15S             ' CH1 TRIGGER PULSE WIDTH READ
    Public Const CnCh1TriggerPulseWidthWrite As Short = &H95S            ' CH1 RIGGER PULSE WIDTH WRITE
    Public Const CnCh1TriggerModeRead As Short = &H16S                   ' CH1 TRIGGER MODE READ
    Public Const CnCh1TriggerModeWrite As Short = &H96S                  ' CH1 RIGGER MODE WRITE
    Public Const CnCh1TriggerStatusRead As Short = &H17S                 ' CH1 TRIGGER STATUS READ
    Public Const CnCh1NoOperation_97 As Short = &H97S
    Public Const CnCh1TriggerEnable As Short = &H98S
    Public Const CnCh1TriggerDisable As Short = &H99S
    Public Const CnCh1TimeTriggerFrequencyRead As Short = &H1AS
    Public Const CnCh1TimeTriggerFrequencyWrite As Short = &H9AS
    Public Const CnCh1ComparatorValueRead As Short = &H1BS
    Public Const CnCh1ComparatorValueWrite As Short = &H9BS
    Public Const CnCh1CompareatorConditionRead As Short = &H1DS
    Public Const CnCh1CompareatorConditionWrite As Short = &H9DS

    ' CH-2 Group Register
    Public Const CnCh2CounterRead As Short = &H20S                       ' CH2 COUNTER READ, 24BIT
    Public Const CnCh2CounterWrite As Short = &HA1S                      ' CH2 COUNTER WRITE
    Public Const CnCh2CounterModeRead As Short = &H21S                   ' CH2 COUNTER MODE READ, 8BIT
    Public Const CnCh2CounterModeWrite As Short = &HA1S                  ' CH2 COUNTER MODE WRITE
    Public Const CnCh2TriggerRegionLowerDataRead As Short = &H22S        ' CH2 TRIGGER REGION LOWER DATA READ, 24BIT
    Public Const CnCh2TriggerRegionLowerDataWrite As Short = &HA2S       ' CH2 TRIGGER REGION LOWER DATA WRITE
    Public Const CnCh2TriggerRegionUpperDataRead As Short = &H23S        ' CH2 TRIGGER REGION UPPER DATA READ, 24BIT
    Public Const CnCh2TriggerRegionUpperDataWrite As Short = &HA3S       ' CH2 TRIGGER REGION UPPER DATA WRITE
    Public Const CnCh2TriggerPeriodRead As Short = &H24S                 ' CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
    Public Const CnCh2TriggerPeriodWrite As Short = &HA4S                ' CH2 TRIGGER PERIOD WRITE
    Public Const CnCh2TriggerPulseWidthRead As Short = &H25S             ' CH2 TRIGGER PULSE WIDTH READ, 24BIT
    Public Const CnCh2TriggerPulseWidthWrite As Short = &HA5S            ' CH2 RIGGER PULSE WIDTH WRITE
    Public Const CnCh2TriggerModeRead As Short = &H26S                   ' CH2 TRIGGER MODE READ
    Public Const CnCh2TriggerModeWrite As Short = &HA6S                  ' CH2 RIGGER MODE WRITE
    Public Const CnCh2TriggerStatusRead As Short = &H27S                 ' CH2 TRIGGER STATUS READ
    Public Const CnCh2NoOperation_A7 As Short = &HA7S
    Public Const CnCh2TriggerEnable As Short = &HA8S
    Public Const CnCh2TriggerDisable As Short = &HA9S
    Public Const CnCh2TimeTriggerFrequencyRead As Short = &H2AS
    Public Const CnCh2TimeTriggerFrequencyWrite As Short = &HAAS
    Public Const CnCh2ComparatorValueRead As Short = &H2BS
    Public Const CnCh2ComparatorValueWrite As Short = &HABS
    Public Const CnCh2CompareatorConditionRead As Short = &H2DS
    Public Const CnCh2CompareatorConditionWrite As Short = &HADS

    ' Ram Access Group Register
    Public Const CnRamDataWithRamAddress As Short = &H30S                ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
    Public Const CnRamDataWrite As Short = &HB0S                         ' RAM DATA WRITE
    Public Const CnRamDataRead As Short = &H31S                          ' RAM DATA READ, 32BIT

    ' Monitor Signal Type Definition                             
    Public Const AxisMode As Short = &H0S
    Public Const JointMode As Short = &H1S
    Public Const ToolMode As Short = &H2S
    Public Const eMonitorSignalType_CmdPos As Short = 0
    Public Const eMonitorSignalType_ActPos As Short = 1
    Public Const eMonitorSignalType_CmdVel As Short = 2
    Public Const eMonitorSignalType_ActVel As Short = 3
    Public Const eMonitorSignalType_CmdAccDec As Short = 4
    Public Const eMonitorSignalType_ActAccDec As Short = 5
    Public Const eMonitorSignalType_PosErr As Short = 6
    Public Const eMonitorSignalType_InMotion As Short = 7
    Public Const eMonitorSignalType_ActTorque As Short = 8
    Public Const eMonitorSignalType_PositionDemand As Short = 9
    Public Const eMonitorSignalType_VelocityDemand As Short = 10
    Public Const eMonitorSignalType_TorqueDemand As Short = 11
    Public Const eMonitorSignalType_MotionAiValue As Short = 12
    Public Const eMonitorSignalType_MotionDiValue As Short = 13
    Public Const eMonitorSignalType_MotionDoValue As Short = 14
    Public Const eMonitorSignalType_Event_ContiEndNode As Short = 15
    ' Digital I/O
    Public Const eMonitorSignalType_DiValue As Short = 16
    Public Const eMonitorSignalType_DoValue As Short = 17
    ' Analog I/O
    Public Const eMonitorSignalType_AiValue As Short = 18
    Public Const eMonitorSignalType_AoValue As Short = 19
    Public Const MAX_eMonitorSignalType As Short = 20

    ' Monitor Operator Type Definition
    Public Const eMonitorOperationType_Grater As Short = 0
    Public Const eMonitorOperationType_Smaller As Short = 1
    Public Const eMonitorOperationType_RisingEdge As Short = 2
    Public Const eMonitorOperationType_FallingEdge As Short = 3
    Public Const MAX_eMonitorOperationType As Short = 4

    ' Monitor Start Option Definition
    Public Const eMonitorStartOption_Immediately As Short = 0
    Public Const eMonitorStartOption_Trigger As Short = 1
    Public Const MAX_eMonitorStartOption As Short = 2

    ' Monitor Overflow Option Definition
    Public Const eMonitorOverflowOption_IgnoreQueueFull As Short = 0
    Public Const eMonitorOverflowOption_WaitQueueFull As Short = 1
    Public Const MAX_eMonitorOverflowOption As Short = 2

    ' HPCPort Data WRITE
    Public Const HpcReset As Short = &H6                     ' Software reset.
    Public Const HpcCommand As Short = &H10
    Public Const HpcData12 As Short = &H12                    ' MSB of data port(31 ~ 16 bit)
    Public Const HpcData34 As Short = &H14                    ' LSB of data port(15 ~ 0 bit)
    Public Const HpcCmStatus As Short = &H1C

    ' HPCPort Channel STATUS
    Public Const HpcCh1Mech As Short = &H20
    Public Const HpcCh1Status As Short = &H22
    Public Const HpcCh2Mech As Short = &H30
    Public Const HpcCh2Status As Short = &H32
    Public Const HpcCh3Mech As Short = &H40
    Public Const HpcCh3Status As Short = &H42
    Public Const HpcCh4Mech As Short = &H50
    Public Const HpcCh4Status As Short = &H52

    ' HPCPort ETC
    Public Const HpcDiIntFlag As Short = &H60
    Public Const HpcDiIntRiseMask As Short = &H62
    Public Const HpcDiIntFallMask As Short = &H64
    Public Const HpcCompIntFlag As Short = &H66
    Public Const HpcCompIntMask As Short = &H68
    Public Const HpcDinData As Short = &H6A
    Public Const HpcDoutData As Short = &H6C

    ' HPCRAM data
    Public Const HpcRamAddr1 As Short = &H70                   ' MSB of Ram address(31  ~ 16 bit)
    Public Const HpcRamAddr2 As Short = &H72                   ' LSB of Ram address(15  ~ 0 bit)

    ' CNT COMMAND LIST
    Public Const HpcCh1CounterRead As Short = &H10                                  ' CH1 COUNTER READ, 32BIT
    Public Const HpcCh1CounterWrite As Short = &H90                                 ' CH1 COUNTER WRITE, 32BIT
    Public Const HpcCh1CounterModeRead As Short = &H11                              ' CH1 COUNTER MODE READ, 4BIT
    Public Const HpcCh1CounterModeWrite As Short = &H91                             ' CH1 COUNTER MODE WRITE, 4BIT
    Public Const HpcCh1TriggerRegionLowerDataRead As Short = &H12                   ' CH1 TRIGGER REGION LOWER DATA READ, 31BIT
    Public Const HpcCh1TriggerRegionLowerDataWrite As Short = &H92                  ' CH1 TRIGGER REGION LOWER DATA WRITE
    Public Const HpcCh1TriggerRegionUpperDataRead As Short = &H13                   ' CH1 TRIGGER REGION UPPER DATA READ, 31BIT
    Public Const HpcCh1TriggerRegionUpperDataWrite As Short = &H93                  ' CH1 TRIGGER REGION UPPER DATA WRITE
    Public Const HpcCh1TriggerPeriodRead As Short = &H14                            ' CH1 TRIGGER PERIOD READ, 31BIT
    Public Const HpcCh1TriggerPeriodWrite As Short = &H94                           ' CH1 TRIGGER PERIOD WRITE
    Public Const HpcCh1TriggerPulseWidthRead As Short = &H15                        ' CH1 TRIGGER PULSE WIDTH READ, 31BIT
    Public Const HpcCh1TriggerPulseWidthWrite As Short = &H95                       ' CH1 RIGGER PULSE WIDTH WRITE
    Public Const HpcCh1TriggerModeRead As Short = &H16                              ' CH1 TRIGGER MODE READ, 8BIT
    Public Const HpcCh1TriggerModeWrite As Short = &H96                             ' CH1 RIGGER MODE WRITE
    Public Const HpcCh1TriggerStatusRead As Short = &H17                            ' CH1 TRIGGER STATUS READ, 8BIT
    Public Const HpcCh1NoOperation_97 As Short = &H97                               ' Reserved.
    Public Const HpcCh1NoOperation_18 As Short = &H17                               ' Reserved.
    Public Const HpcCh1TriggerEnable As Short = &H98                                ' CH1 TRIGGER ENABLE.
    Public Const HpcCh1NoOperation_19 As Short = &H19                               ' Reserved.
    Public Const HpcCh1TriggerDisable As Short = &H99                               ' CH1 TRIGGER DISABLE.
    Public Const HpcCh1TimeTriggerFrequencyRead As Short = &H1A                     ' CH1 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    Public Const HpcCh1TimeTriggerFrequencyWrite As Short = &H9A                    ' CH1 TRIGGER FREQUNCE INFO. READ
    Public Const HpcCh1Comparator1ValueRead As Short = &H1B                         ' CH1 COMPAREATOR1 READ, 31BIT
    Public Const HpcCh1Comparator1ValueWrite As Short = &H9B                        ' CH1 COMPAREATOR1 WRITE, 31BIT
    Public Const HpcCh1Comparator2ValueRead As Short = &H1C                         ' CH1 COMPAREATOR2 READ, 31BIT
    Public Const HpcCh1Comparator2ValueWrite As Short = &H9C                        ' CH1 COMPAREATOR2 WRITE, 31BIT
    Public Const HpcCh1CompareatorConditionRead As Short = &H1D                     ' CH1 COMPAREATOR CONDITION READ, 4BIT
    Public Const HpcCh1CompareatorConditionWrite As Short = &H9D                    ' CH1 COMPAREATOR CONDITION WRITE, 4BIT
    Public Const HpcCh1AbsTriggerTopPositionRead As Short = &H1E                    ' CH1 ABS TRIGGER POSITION READ, 31BIT
    Public Const HpcCh1AbsTriggerPositionWrite As Short = &H9E                      ' CH1 ABS TRIGGER POSITION WRITE, 31BIT
    Public Const HpcCh1AbsTriggerFifoStatusRead As Short = &H1F                     ' CH1 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    Public Const HpcCh1AbsTriggerPositionClear As Short = &H9F                      ' CH1 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-2 Group Register
    Public Const HpcCh2CounterRead As Short = &H20                                  ' CH2 COUNTER READ, 32BIT
    Public Const HpcCh2CounterWrite As Short = &HA0                                 ' CH2 COUNTER WRITE, 32BIT
    Public Const HpcCh2CounterModeRead As Short = &H21                              ' CH2 COUNTER MODE READ, 4BIT
    Public Const HpcCh2CounterModeWrite As Short = &HA1                             ' CH2 COUNTER MODE WRITE, 4BIT
    Public Const HpcCh2TriggerRegionLowerDataRead As Short = &H22                   ' CH2 TRIGGER REGION LOWER DATA READ, 31BIT
    Public Const HpcCh2TriggerRegionLowerDataWrite As Short = &HA2                  ' CH2 TRIGGER REGION LOWER DATA WRITE
    Public Const HpcCh2TriggerRegionUpperDataRead As Short = &H23                   ' CH2 TRIGGER REGION UPPER DATA READ, 31BIT
    Public Const HpcCh2TriggerRegionUpperDataWrite As Short = &HA3                  ' CH2 TRIGGER REGION UPPER DATA WRITE
    Public Const HpcCh2TriggerPeriodRead As Short = &H24                            ' CH2 TRIGGER PERIOD READ, 31BIT
    Public Const HpcCh2TriggerPeriodWrite As Short = &HA4                           ' CH2 TRIGGER PERIOD WRITE
    Public Const HpcCh2TriggerPulseWidthRead As Short = &H25                        ' CH2 TRIGGER PULSE WIDTH READ, 31BIT
    Public Const HpcCh2TriggerPulseWidthWrite As Short = &HA5                       ' CH2 RIGGER PULSE WIDTH WRITE
    Public Const HpcCh2TriggerModeRead As Short = &H26                              ' CH2 TRIGGER MODE READ, 8BIT
    Public Const HpcCh2TriggerModeWrite As Short = &HA6                             ' CH2 RIGGER MODE WRITE
    Public Const HpcCh2TriggerStatusRead As Short = &H27                            ' CH2 TRIGGER STATUS READ, 8BIT
    Public Const HpcCh2NoOperation_97 As Short = &HA7                               ' Reserved.
    Public Const HpcCh2NoOperation_18 As Short = &H27                               ' Reserved.
    Public Const HpcCh2TriggerEnable As Short = &HA8                                ' CH2 TRIGGER ENABLE.
    Public Const HpcCh2NoOperation_19 As Short = &H29                               ' Reserved.
    Public Const HpcCh2TriggerDisable As Short = &HA9                               ' CH2 TRIGGER DISABLE.
    Public Const HpcCh2TimeTriggerFrequencyRead As Short = &H2A                     ' CH2 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    Public Const HpcCh2TimeTriggerFrequencyWrite As Short = &HAA                    ' CH2 TRIGGER FREQUNCE INFO. READ
    Public Const HpcCh2Comparator1ValueRead As Short = &H2B                         ' CH2 COMPAREATOR1 READ, 31BIT
    Public Const HpcCh2Comparator1ValueWrite As Short = &HAB                        ' CH2 COMPAREATOR1 WRITE, 31BIT
    Public Const HpcCh2Comparator2ValueRead As Short = &H2C                         ' CH2 COMPAREATOR2 READ, 31BIT
    Public Const HpcCh2Comparator2ValueWrite As Short = &HAC                        ' CH2 COMPAREATOR2 WRITE, 31BIT
    Public Const HpcCh2CompareatorConditionRead As Short = &H2D                     ' CH2 COMPAREATOR CONDITION READ, 4BIT
    Public Const HpcCh2CompareatorConditionWrite As Short = &HAD                    ' CH2 COMPAREATOR CONDITION WRITE, 4BIT
    Public Const HpcCh2AbsTriggerTopPositionRead As Short = &H2E                    ' CH2 ABS TRIGGER POSITION READ, 31BIT
    Public Const HpcCh2AbsTriggerPositionWrite As Short = &HAE                      ' CH2 ABS TRIGGER POSITION WRITE, 31BIT
    Public Const HpcCh2AbsTriggerFifoStatusRead As Short = &H2F                     ' CH2 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    Public Const HpcCh2AbsTriggerPositionClear As Short = &HAF                      ' CH2 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-3 Group Register
    Public Const HpcCh3CounterRead As Short = &H30                                  ' CH3 COUNTER READ, 32BIT
    Public Const HpcCh3CounterWrite As Short = &HB0                                 ' CH3 COUNTER WRITE, 32BIT
    Public Const HpcCh3CounterModeRead As Short = &H31                              ' CH3 COUNTER MODE READ, 4BIT
    Public Const HpcCh3CounterModeWrite As Short = &HB1                             ' CH3 COUNTER MODE WRITE, 4BIT
    Public Const HpcCh3TriggerRegionLowerDataRead As Short = &H32                   ' CH3 TRIGGER REGION LOWER DATA READ, 31BIT
    Public Const HpcCh3TriggerRegionLowerDataWrite As Short = &HB2                  ' CH3 TRIGGER REGION LOWER DATA WRITE
    Public Const HpcCh3TriggerRegionUpperDataRead As Short = &H33                   ' CH3 TRIGGER REGION UPPER DATA READ, 31BIT
    Public Const HpcCh3TriggerRegionUpperDataWrite As Short = &HB3                  ' CH3 TRIGGER REGION UPPER DATA WRITE
    Public Const HpcCh3TriggerPeriodRead As Short = &H34                            ' CH3 TRIGGER PERIOD READ, 31BIT
    Public Const HpcCh3TriggerPeriodWrite As Short = &HB4                           ' CH3 TRIGGER PERIOD WRITE
    Public Const HpcCh3TriggerPulseWidthRead As Short = &H35                        ' CH3 TRIGGER PULSE WIDTH READ, 31BIT
    Public Const HpcCh3TriggerPulseWidthWrite As Short = &HB5                       ' CH3 RIGGER PULSE WIDTH WRITE
    Public Const HpcCh3TriggerModeRead As Short = &H36                              ' CH3 TRIGGER MODE READ, 8BIT
    Public Const HpcCh3TriggerModeWrite As Short = &HB6                             ' CH3 RIGGER MODE WRITE
    Public Const HpcCh3TriggerStatusRead As Short = &H37                            ' CH3 TRIGGER STATUS READ, 8BIT
    Public Const HpcCh3NoOperation_97 As Short = &HB7                               ' Reserved.
    Public Const HpcCh3NoOperation_18 As Short = &H37                               ' Reserved.
    Public Const HpcCh3TriggerEnable As Short = &HB8                                ' CH3 TRIGGER ENABLE.
    Public Const HpcCh3NoOperation_19 As Short = &H39                               ' Reserved.
    Public Const HpcCh3TriggerDisable As Short = &HB9                               ' CH3 TRIGGER DISABLE.
    Public Const HpcCh3TimeTriggerFrequencyRead As Short = &H3A                     ' CH3 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    Public Const HpcCh3TimeTriggerFrequencyWrite As Short = &HBA                    ' CH3 TRIGGER FREQUNCE INFO. READ
    Public Const HpcCh3Comparator1ValueRead As Short = &H3B                         ' CH3 COMPAREATOR1 READ, 31BIT
    Public Const HpcCh3Comparator1ValueWrite As Short = &HBB                        ' CH3 COMPAREATOR1 WRITE, 31BIT
    Public Const HpcCh3Comparator2ValueRead As Short = &H3C                         ' CH3 COMPAREATOR2 READ, 31BIT
    Public Const HpcCh3Comparator2ValueWrite As Short = &HBC                        ' CH3 COMPAREATOR2 WRITE, 31BIT
    Public Const HpcCh3CompareatorConditionRead As Short = &H3D                     ' CH3 COMPAREATOR CONDITION READ, 4BIT
    Public Const HpcCh3CompareatorConditionWrite As Short = &HBD                    ' CH3 COMPAREATOR CONDITION WRITE, 4BIT
    Public Const HpcCh3AbsTriggerTopPositionRead As Short = &H3E                    ' CH3 ABS TRIGGER POSITION READ, 31BIT
    Public Const HpcCh3AbsTriggerPositionWrite As Short = &HBE                      ' CH3 ABS TRIGGER POSITION WRITE, 31BIT
    Public Const HpcCh3AbsTriggerFifoStatusRead As Short = &H3F                     ' CH3 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    Public Const HpcCh3AbsTriggerPositionClear As Short = &HBF                      ' CH3 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-4 Group Register
    Public Const HpcCh4CounterRead As Short = &H40                                  ' CH4 COUNTER READ, 32BIT
    Public Const HpcCh4CounterWrite As Short = &HC0                                 ' CH4 COUNTER WRITE, 32BIT
    Public Const HpcCh4CounterModeRead As Short = &H41                              ' CH4 COUNTER MODE READ, 4BIT
    Public Const HpcCh4CounterModeWrite As Short = &HC1                             ' CH4 COUNTER MODE WRITE, 4BIT
    Public Const HpcCh4TriggerRegionLowerDataRead As Short = &H42                   ' CH4 TRIGGER REGION LOWER DATA READ, 31BIT
    Public Const HpcCh4TriggerRegionLowerDataWrite As Short = &HC2                  ' CH4 TRIGGER REGION LOWER DATA WRITE
    Public Const HpcCh4TriggerRegionUpperDataRead As Short = &H43                   ' CH4 TRIGGER REGION UPPER DATA READ, 31BIT
    Public Const HpcCh4TriggerRegionUpperDataWrite As Short = &HC3                  ' CH4 TRIGGER REGION UPPER DATA WRITE
    Public Const HpcCh4TriggerPeriodRead As Short = &H44                            ' CH4 TRIGGER PERIOD READ, 31BIT
    Public Const HpcCh4TriggerPeriodWrite As Short = &HC4                           ' CH4 TRIGGER PERIOD WRITE
    Public Const HpcCh4TriggerPulseWidthRead As Short = &H45                        ' CH4 TRIGGER PULSE WIDTH READ, 31BIT
    Public Const HpcCh4TriggerPulseWidthWrite As Short = &HC5                       ' CH4 RIGGER PULSE WIDTH WRITE
    Public Const HpcCh4TriggerModeRead As Short = &H46                              ' CH4 TRIGGER MODE READ, 8BIT
    Public Const HpcCh4TriggerModeWrite As Short = &HC6                             ' CH4 RIGGER MODE WRITE
    Public Const HpcCh4TriggerStatusRead As Short = &H47                            ' CH4 TRIGGER STATUS READ, 8BIT
    Public Const HpcCh4NoOperation_97 As Short = &HC7                               ' Reserved.
    Public Const HpcCh4NoOperation_18 As Short = &H47                               ' Reserved.
    Public Const HpcCh4TriggerEnable As Short = &HC8                                ' CH4 TRIGGER ENABLE.
    Public Const HpcCh4NoOperation_19 As Short = &H49                               ' Reserved.
    Public Const HpcCh4TriggerDisable As Short = &HC9                               ' CH4 TRIGGER DISABLE.
    Public Const HpcCh4TimeTriggerFrequencyRead As Short = &H4A                     ' CH4 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    Public Const HpcCh4TimeTriggerFrequencyWrite As Short = &HCA                    ' CH4 TRIGGER FREQUNCE INFO. READ
    Public Const HpcCh4Comparator1ValueRead As Short = &H4B                         ' CH4 COMPAREATOR1 READ, 31BIT
    Public Const HpcCh4Comparator1ValueWrite As Short = &HCB                        ' CH4 COMPAREATOR1 WRITE, 31BIT
    Public Const HpcCh4Comparator2ValueRead As Short = &H4C                         ' CH4 COMPAREATOR2 READ, 31BIT
    Public Const HpcCh4Comparator2ValueWrite As Short = &HCC                        ' CH4 COMPAREATOR2 WRITE, 31BIT
    Public Const HpcCh4CompareatorConditionRead As Short = &H4D                     ' CH4 COMPAREATOR CONDITION READ, 4BIT
    Public Const HpcCh4CompareatorConditionWrite As Short = &HCD                    ' CH4 COMPAREATOR CONDITION WRITE, 4BIT
    Public Const HpcCh4AbsTriggerTopPositionRead As Short = &H4E                    ' CH4 ABS TRIGGER POSITION READ, 31BIT
    Public Const HpcCh4AbsTriggerPositionWrite As Short = &HCE                      ' CH4 ABS TRIGGER POSITION WRITE, 31BIT
    Public Const HpcCh4AbsTriggerFifoStatusRead As Short = &H4F                     ' CH4 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    Public Const HpcCh4AbsTriggerPositionClear As Short = &HCF                      ' CH4 ABS TRIGGER POSITION FIFO CLEAR

    ' Ram Access Group Register
    Public Const HpcRamDataWithRamAddress As Short = &H51                           ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
    Public Const HpcRamDataWrite As Short = &HD0                                    ' RAM DATA WRITE
    Public Const HpcRamDataRead As Short = &H50                                     ' RAM DATA READ, 32BIT

    ' Debugging Registers
    Public Const HpcCh1TrigPosIndexRead As Short = &H60                             ' CH1 Current RAM trigger index position on 32Bit data, 8BIT
    Public Const HpcCh1TrigBackwardDataRead As Short = &H61                         ' CH1 Current RAM trigger backward position data, 32BIT
    Public Const HpcCh1TrigCurrentDataRead As Short = &H62                          ' CH1 Current RAM trigger current position data, 32BIT
    Public Const HpcCh1TrigForwardDataRead As Short = &H63                          ' CH1 Current RAM trigger next position data, 32BIT
    Public Const HpcCh1TrigRamAddressRead As Short = &H64                           ' CH1 Current RAM trigger address, 20BIT

    Public Const HpcCh2TrigPosIndexRead As Short = &H65                             ' CH2 Current RAM trigger index position on 32Bit data, 8BIT
    Public Const HpcCh2TrigBackwardDataRead As Short = &H66                         ' CH2 Current RAM trigger backward position data, 32BIT
    Public Const HpcCh2TrigCurrentDataRead As Short = &H67                          ' CH2 Current RAM trigger current position data, 32BIT
    Public Const HpcCh2TrigForwardDataRead As Short = &H68                          ' CH2 Current RAM trigger next position data, 32BIT
    Public Const HpcCh2TrigRamAddressRead As Short = &H69                           ' CH2 Current RAM trigger address, 20BIT

    Public Const HpcCh3TrigPosIndexRead As Short = &H70                             ' CH3 Current RAM trigger index position on 32Bit data, 8BIT
    Public Const HpcCh3TrigBackwardDataRead As Short = &H71                         ' CH3 Current RAM trigger backward position data, 32BIT
    Public Const HpcCh3TrigCurrentDataRead As Short = &H72                          ' CH3 Current RAM trigger current position data, 32BIT
    Public Const HpcCh3TrigForwardDataRead As Short = &H73                          ' CH3 Current RAM trigger next position data, 32BIT
    Public Const HpcCh3TrigRamAddressRead As Short = &H74                           ' CH3 Current RAM trigger address, 20BIT

    Public Const HpcCh4TrigPosIndexRead As Short = &H75                             ' CH4 Current RAM trigger index position on 32Bit data, 8BIT
    Public Const HpcCh4TrigBackwardDataRead As Short = &H76                         ' CH4 Current RAM trigger backward position data, 32BIT
    Public Const HpcCh4TrigCurrentDataRead As Short = &H77                          ' CH4 Current RAM trigger current position data, 32BIT
    Public Const HpcCh4TrigForwardDataRead As Short = &H78                          ' CH4 Current RAM trigger next position data, 32BIT
    Public Const HpcCh4TrigRamAddressRead As Short = &H79                           ' CH4 Current RAM trigger address, 20BIT

    Public Const HpcCh1TestEnable As Short = &H81                                   ' CH1 test enable(Manufacturer only)
    Public Const HpcCh2TestEnable As Short = &H82                                   ' CH2 test enable(Manufacturer only)
    Public Const HpcCh3TestEnable As Short = &H83                                   ' CH3 test enable(Manufacturer only)
    Public Const HpcCh4TestEnable As Short = &H84                                   ' CH4 test enable(Manufacturer only)

    Public Const HpcTestFrequency As Short = &H8C                                   ' Test counter output frequency(32bit)
    Public Const HpcTestCountStart As Short = &H8D                                  ' Start test counter output with position(32bit signed).
    Public Const HpcTestCountEnd As Short = &H8E                                    ' End counter output.

    Public Const HpcCh1TrigVectorTopDataOfFifo As Short = &H54                      ' CH1 UnitVector X positin of FIFO top.
    Public Const HpcCh1TrigVectorFifoStatus As Short = &H55                         ' CH1 UnitVector X FIFO Status.
    Public Const HpcCh2TrigVectorTopDataOfFifo As Short = &H56                      ' CH2 UnitVector Y positin of FIFO top.
    Public Const HpcCh2TrigVectorFifoStatus As Short = &H57                         ' CH2 UnitVector Y FIFO Status.
    Public Const HpcCh1TrigVectorFifoPush As Short = &HD2                           ' CH1 UnitVector X position, fifo data push.
    Public Const HpcCh2TrigVectorFifoPush As Short = &HD3                           ' CH2 UnitVector Y position, fifo data push.

    Public Const AXP_MAX_MACRO_SIZE As Short      = 8
    Public Const AXP_MAX_MACRO_NODE_NUM As Short  = 64
    Public Const AXP_MAX_MACRO_SET_ARG As Short   = 16
    Public Const AXP_MAX_MACRO_GET_DATA As Short  = 16
    Public Const AXP_MAX_MACRO_DATA_BYTE As Short = 12
    
    Public Const MACRO_FUNC_CALL As Short               = 0
    Public Const MACRO_FUNC_JUMP As Short               = 1
    Public Const MACRO_FUNC_RETURN As Short             = 2
    Public Const MACRO_FUNC_REPEAT As Short             = 3
    Public Const MACRO_FUNC_SET_OUTPUT As Short         = 4
    Public Const MACRO_FUNC_WAIT As Short               = 5
    Public Const MACRO_FUNC_STOP As Short               = 6
    Public Const MACRO_FUNC_MAX As Short                = 7
    
    Public Const MACRO_JUMP_MACRO As Short              = 0
    Public Const MACRO_JUMP_NODE As Short               = 1
    
    Public Const MACRO_DIGITAL_OUTPUT As Short          = 0
    Public Const MACRO_ANALOG_OUTPUT As Short           = 1
    Public Const MACRO_MOTION_OUTPUT As Short           = 2
    
    Public Const MACRO_DATA_BIT As Short                = 0
    Public Const MACRO_DATA_BYTE As Short               = 1
    Public Const MACRO_DATA_WORD As Short               = 2
    Public Const MACRO_DATA_DWORD As Short              = 3
    Public Const MACRO_DATA_BYTE12 As Short             = 4
    Public Const MACRO_DATA_VOLTAGE As Short            = 5
    Public Const MACRO_DATA_DIGIT As Short              = 6
    
    Public Const MACRO_QUICK_STOP As Short              = 0
    Public Const MACRO_SLOW_STOP As Short               = 1
    
    Public Const MACRO_START_READY As Short             = 0
    Public Const MACRO_START_IMMEDIATE As Short         = 1
    
    Public Const MACRO_STATUS_STOP As Short             = 0
    Public Const MACRO_STATUS_READY As Short            = 1
    Public Const MACRO_STATUS_RUN As Short              = 2
    Public Const MACRO_STATUS_ERROR As Short            = 3
    
    Public Const ERROR_INVALID_MACRO_NO As Short        = 1
    Public Const ERROR_INVALID_NODE_NO As Short         = 2
    Public Const ERROR_INVALID_MODULE_NO As Short       = 3
    Public Const ERROR_INVALID_AXIS_NO As Short         = 4
    Public Const ERROR_INVALID_CHANNEL_NO As Short      = 5
    Public Const ERROR_INVALID_JUMP_TYPE As Short       = 6
    Public Const ERROR_INVALID_OUTPUT_TYPE As Short     = 7
    Public Const ERROR_INVALID_OFFSET As Short          = 8
    Public Const ERROR_INVALID_STOP_MODE As Short       = 9
    Public Const ERROR_INVALID_START_CONDITION As Short = 10
    Public Const ERROR_NOT_SUPPORT_MODULE As Short      = 11
    Public Const ERROR_NOT_READY_MACRO As Short         = 12

End Module
