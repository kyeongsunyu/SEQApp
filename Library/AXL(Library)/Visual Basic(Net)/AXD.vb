Option Strict Off
Option Explicit On
Module AXD

    '*****************************************************************************
    '/****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ----------
    '**
    '** AXD.VB
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Digital Library Header File
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
    '*/
    '


'========== Board and module information =================================================================================

' Verify if DIO module exists
Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer


' Verify DIO in/output module number
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer


' Verify the number of DIO in/output module
Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer


' Verify the number of input contacts of specified module
Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer


' Verify the number of output contacts of specified module
Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer


' Verify the base board number, module position and module ID with specified module number
Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer


' Verify specified module board : Sub ID, module name, module description
'===============================================/
' support product : EtherCAT
' upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
' szModuleName         : model name of module(50 Bytes)
' szModuleDescription  : description of module(80 Bytes)
'======================================================'
Public Declare Function AxdInfoGetModuleEx Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upModuleSubID As Integer, ByVal szModuleName As String, ByVal szModuleDescription As String) As Integer

' Verify Module status of specified module board
Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

'========== Verification group for input interrupt setting =================================================================================
' Use window message, callback API or event method in order to get interrupt message into specified module
'========= Interrupt-related function ======================================================================================
'The callback function method has the advantage that the event can be notified very quickly because the callback function is called immediately at the time of the occurrence of the event.
'But, The main process is stalled until the callback function is completely terminated.
'In other words, Care must be taken when there is work load in the callback function.
'The event method is a method of continuously detecting and processing the occurrence of an interrupt by using a thread.
'The event method has the disadvantage that system resources are occupied by thread, but it has the advantage that interrupts can be detected and processed the fastest.
'This method is not commonly used. but it is used when quick interrupt handling is main concern.
'The event method uses a specific thread to monitor the occurrence of an event, and it works independently of the main process.
'So, This is the recommended method because it enables the most efficient use of resources in a multiprocessor system.
'Use a Window message or callback function to receive interrupt message.
'(Message handle, Message ID, Callback function, Interrupt event)
'    hWnd        : Used to receive window handles and window messages. If not, enter NULL.
'    uMessage    : Massage of window handle. To not use this or use the default value, enter 0.
'    proc        : Pointer of the function to be called when an interrupt occurs. To not use this, enter NULL.
'    pEvent      : Event handling when using event method.
' Ex)
' AxdiInterruptSetModule(0, Null, 0, AxtInterruptProc, NULL);
' void __stdcall AxtInterruptProc(long lActiveNo, DWORD uFlag){
'     ... ;
' }
Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal hWnd As Integer, ByVal uMessage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer


' Set whether to use interrupt of specified module
'======================================================'
' uUse       : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer


' Verify whether to use interrupt of specified module
'======================================================'
' *upUse     : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer


' Verify the position interrupt occurred
Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Integer, ByRef upFlag As Integer) As Integer


'========== Input interrupt rising / Verification group for setting of interrupt occurrence in falling edge =================================================================================

' Set the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer


' Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer


' Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer


' Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer


' Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer


' Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer


' Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer


' Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer


' Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer


' Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer


'========== Verification group of input / output signal level setting =================================================================================
'==Verification group of input signal level setting
' Set data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Verify data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Set data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lOffset     : Offset position for input contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Verify data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


'==Verification group of output signal level setting
' Set data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Verify data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Verify data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


' Set data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Verify data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer


'========== Input / Output signal reading / writing =================================================================================
'==Output signal writing
' Output data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by word unit in Offset position of specified output contact module
'==============================================================================================='
' uValue     : 0x00 ~ 0x0FFFF
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

'==Output signal reading
' Read data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

' ==Input signal reading
' Read data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lOffset     : Offset position for input contact
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by wordt unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer



'== Only for MLII, M-Systems DIO(R7 series)
' Read data level by bit unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by byte unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by byte unit between input index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by word unit between input index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by double word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by dword unit between input index.(0)
' *upValue    : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Read data level by double word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' *upValue    : 0x00 ~ 0x0000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Output data by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' uValue      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Output data by dword unit in Offset position of specified extended output contact module
'==============================================================================================/'
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' uValue      : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer


' Set data level by bit unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Set data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer


' Verify data level by bit unit in Offset position of specified extended input/output contact module
'===============================================================================================//'
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'===============================================================================================//'
Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer


' Verify data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer


' Verify data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer


' Verify data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer


'========== Advanced API =================================================================================0
' Verify if the signal was switched from Off to On in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' *upValue   : FALSE(0)
'            : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Verify if the signal was switched from On to Off in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' *upValue    : FALSE(0)
'             : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


' Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' lCount      : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue    : FALSE(0)
'             : TRUE(1)
' lStart      : 1
'             : 0
'==============================================================================================='
Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer


' Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' lCount      : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue    : FALSE(0)
'             : TRUE(1)
' lStart      : 1(First call)
'             : 0(Repeat call)
'==============================================================================================='
Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer


' Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lCount      : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec       : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer


' Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lCount      : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec       : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer


' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lInitState  : Off(0)
'             : On(1)
' lmSecOn     : 1 ~ 30000
' lmSecOff    : 1 ~ 30000
' lCount      : 1 ~ 0x7FFFFFFF(2147483647)
'             : -1
'==============================================================================================='
Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lInitState As Integer, ByVal lmSecOn As Integer, ByVal lmSecOff As Integer, ByVal lCount As Integer) As Integer


' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' uOnOff      : Off(0)
'             : On(1)
'==============================================================================================='
Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uOnOff As Integer) As Integer


' In disconnect cases Set output status of specified module by byte.
'==============================================================================================='
' lModuleNo   : Module number
' dwSize      : Set Byte Number(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
' dwaSetValue : Set Value(Default : Status before Disconnect)
'             : 0 --> Disconnect before Status
'             : 1 --> On
'             : 2 --> Off
'             : 3 --> User Value, (Default user value : 'Off', Changeable from 'AxdoSetNetworkErrorUserValue()'). (SIII / ML3 / ECAT only)
'==============================================================================================='
Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwSize As Integer, ByRef dwaSetValue As Integer) As Integer


' API function for setting user defined output value in bytes when specified output module network is broken. (SIII / ML3 / ECAT only)
'==============================================================================================='
' lModuleNo   : Module number(Support dispersion type slaves only)
' dwOffset    : Offset position by dword unit between output index, Increasing unit of byte(Designation range:0, 1, 2, 3)
' dwValue     : Output contact value(00 ~ FFH)
'             : It must be set to 'User Value' for corresponding offset by 'AxdoSetNetworkErrorAct()'
'==============================================================================================='
Public Declare Function AxdoSetNetworkErrorUserValue Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwOffset As Integer, ByVal dwValue As Integer) As Integer


' Setting connection number of specified module.
Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwInputNum As Integer, ByVal dwOutputNum As Integer) As Integer


' Verifying connection number of specified module.
Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpInputNum As Integer, ByRef dwpOutputNum As Integer) As Integer




'== API for EtherCAT.
' Output data by bit length in Offset position of specified output module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between output index
' dwDataBitLength  : Bit length of output data
' pbyData          : The pointer of output data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer

' Read data by bit length in Offset position of specified input module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between input index
' dwDataBitLength  : Bit length of output data
' pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiReadInportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer

' Read data by bit length in Offset position of specified output module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between output index
' dwDataBitLength  : Bit length of input data
' pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoReadOutportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer

    Public Declare Function AxdoLinkSetOutport Lib "AXL.dll" (ByVal lLinkNo As Integer, ByVal lDstModuleNo As Integer, ByVal uDstBitOffset As Integer, ByVal lSrcModuleNo As Integer, ByVal uSrcBitOffset As Integer, ByVal uSrcDataBitLength As Integer, ByVal uSrcPortType As Integer) As Integer
    Public Declare Function AxdoLinkGetOutport Lib "AXL.dll" (ByVal lLinkNo As Integer, ByRef lpDstModuleNo As Integer, ByRef upDstBitOffset As Integer, ByRef lpSrcModuleNo As Integer, ByRef upSrcBitOffset As Integer, ByRef upSrcDataBitLength As Integer, ByRef upSrcPortType As Integer) As Integer
    Public Declare Function AxdoLinkResetOutport Lib "AXL.dll" (ByVal lLinkNo As Integer) As Integer

    Public Declare Function AxdoInterLockSetOutport Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lInterLockNo As Integer, ByVal lDstModuleNo As Integer, ByVal uDstBitOffset As Integer, ByVal lSrcModuleNo As Integer, ByVal uSrcBitOffset As Integer, ByVal uSrcPortType As Integer, ByVal uSrcCondition As Integer, ByVal uOutputMode As Integer, ByVal uOutputModeData As Integer) As Integer
    Public Declare Function AxdoInterLockGetOutport Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lInterLockNo As Integer, ByRef lpDstModuleNo As Integer, ByRef upDstBitOffset As Integer, ByRef lpSrcModuleNo As Integer, ByRef upSrcBitOffset As Integer, ByRef upSrcPortType As Integer, ByRef upSrcCondition As Integer, ByRef upOutputMode As Integer, ByRef upOutputModeData As Integer) As Integer
    Public Declare Function AxdoInterLockIsEnabled Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lInterLockNo As Integer, ByRef upEnabled As Integer) As Integer
    Public Declare Function AxdoInterLockResetOutport Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lInterLockNo As Integer) As Integer


End Module
