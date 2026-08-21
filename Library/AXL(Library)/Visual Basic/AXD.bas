'*****************************************************************************
'/****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ----------
'**
'** AXD.BAS
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

Attribute VB_Name = "AXD"



'========== Board and module information =================================================================================

' Verify if DIO module exists
Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Long) As Long


' Verify DIO in/output module number
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long


' Verify the number of DIO in/output module
Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long


' Verify the number of input contacts of specified module
Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long


' Verify the number of output contacts of specified module
Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long


' Verify the base board number, module position and module ID with specified module number
Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long


' Verify specified module board : Sub ID, module name, module description
'===============================================/
' support product : EtherCAT
' upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
' szModuleName         : model name of module(50 Bytes)
' szModuleDescription  : description of module(80 Bytes)
'======================================================'
Public Declare Function AxdInfoGetModuleEx Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upModuleSubID As Long, ByRef szModuleName As String, ByRef szModuleDescription As String) As Long

' Verify Module status of specified module board
Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long


'========== Verification group for input interrupt setting
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
Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal hWnd As Long, ByVal uMessage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long


' Set whether to use interrupt of specified module
'======================================================'
' uUse       : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long


' Verify whether to use interrupt of specified module
'======================================================'
' *upUse     : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long


' Verify the position interrupt occurred
Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Long, ByRef upFlag As Long) As Long


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
Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long


' Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long


' Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long


' Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long


' Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long


' Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long


' Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long


' Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lModuleNo : Number of module
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long


' Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long


' Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' lOffset   : Offset position for input contact
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long


'========== Verification group of input / output signal level setting =================================================================================
'==Verification group of input signal level setting
' Set data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Verify data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Set data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lOffset     : Offset position for input contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Verify data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long


'==Verification group of output signal level setting
' Set data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Verify data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Verify data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Set data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Verify data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long


'========== Input / Output signal reading / writing =================================================================================
'==Output signal writing
' Output data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by word unit in Offset position of specified output contact module
'==============================================================================================='
' uValue     : 0x00 ~ 0x0FFFF
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' uValue      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

'==Output signal reading
' Read data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data by word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for output contact
' *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


'==Input signal reading
' Read data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' lOffset     : Offset position for input contact
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by wordt unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Number of module
' lOffset     : Offset position for input contact
' *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
'==============================================================================================='
Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long



'== Only for MLII, M-Systems DIO(R7 series)
' Read data level by bit unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by byte unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by byte unit between input index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by word unit between input index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by double word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by dword unit between input index.(0)
' *upValue    : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Read data level by double word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' *upValue    : 0x00 ~ 0x0000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Output data by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' uValue      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Output data by dword unit in Offset position of specified extended output contact module
'==============================================================================================/'
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' uValue    : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long


' Set data level by bit unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Set data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long


' Verify data level by bit unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long


' Verify data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long


' Verify data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long


' Verify data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long


'========== Advanced API =================================================================================

' Verify if the signal was switched from Off to On in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' *upValue   : FALSE(0)
'            : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Verify if the signal was switched from On to Off in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' *upValue   : FALSE(0)
'            : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long


' Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue   : FALSE(0)
'            : TRUE(1)
' lStart     : 1
'            : 0
'==============================================================================================='
Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long


' Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for input contact
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue   : FALSE(0)
'            : TRUE(1)
' lStart      : 1(First call)
'             : 0(Repeat call)
'==============================================================================================='
Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long


' Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec      : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long


' Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec      : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long


' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' lInitState : Off(0)
'            : On(1)
' lmSecOn    : 1 ~ 30000
' lmSecOff   : 1 ~ 30000
' lCount     : 1 ~ 0x7FFFFFFF(2147483647)
'            : -1
'==============================================================================================='
Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lInitState As Long, ByVal lmSecOn As Long, ByVal lmSecOff As Long, ByVal lCount As Long) As Long


' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position for output contact
' uOnOff     : Off(0)
'            : On(1)
'==============================================================================================='
Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uOnOff As Long) As Long


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
Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwSize As Long, ByRef dwaSetValue As Long) As Long


' API function for setting user defined output value in bytes when specified output module network is broken. (SIII / ML3 / ECAT only)
'==============================================================================================='
' lModuleNo   : Module number(Support dispersion type slaves only)
' dwOffset    : Offset position by dword unit between output index, Increasing unit of byte(Designation range:0, 1, 2, 3)
' dwValue     : Output contact value(00 ~ FFH)
'             : It must be set to 'User Value' for corresponding offset by 'AxdoSetNetworkErrorAct()'
'==============================================================================================='
Public Declare Function AxdoSetNetworkErrorUserValue Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwOffset As Long, ByVal dwValue As Long) As Long


' Setting connection number of specified module.
Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwInputNum As Long, ByVal dwOutputNum As Long) As Long


' Verifying connection number of specified module.
Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpInputNum As Long, ByRef dwpOutputNum As Long) As Long




'== API for EtherCAT.
' Output data by bit length in Offset position of specified output module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between output index
' dwDataBitLength  : Bit length of output data
' pbyData          : The pointer of output data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoWriteOutportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long

' Read data by bit length in Offset position of specified input module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between input index
' dwDataBitLength  : Bit length of output data
' pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdiReadInportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long

' Read data by bit length in Offset position of specified output module
'===============================================================================================//
' lModuleNo        : Module number
' dwBitOffset      : Bit offset position by dword unit between output index
' dwDataBitLength  : Bit length of input data
' pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
'==============================================================================================='
Public Declare Function AxdoReadOutportByBitOffset Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long

    Public Declare Function AxdoLinkSetOutport Lib "AXL.dll" (ByVal lLinkNo As Long, ByVal lDstModuleNo As Long, ByVal uDstBitOffset As Long, ByVal lSrcModuleNo As Long, ByVal uSrcBitOffset As Long, ByVal uSrcDataBitLength As Long, ByVal uSrcPortType As Long) As Long
    Public Declare Function AxdoLinkGetOutport Lib "AXL.dll" (ByVal lLinkNo As Long, ByRef lpDstModuleNo As Long, ByRef upDstBitOffset As Long, ByRef lpSrcModuleNo As Long, ByRef upSrcBitOffset As Long, ByRef upSrcDataBitLength As Long, ByRef upSrcPortType As Long) As Long
    Public Declare Function AxdoLinkResetOutport Lib "AXL.dll" (ByVal lLinkNo As Long) As Long

    Public Declare Function AxdoInterLockSetOutport Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lInterLockNo As Long, ByVal lDstModuleNo As Long, ByVal uDstBitOffset As Long, ByVal lSrcModuleNo As Long, ByVal uSrcBitOffset As Long, ByVal uSrcPortType As Long, ByVal uSrcCondition As Long, ByVal uOutputMode As Long, ByVal uOutputModeData As Long) As Long
    Public Declare Function AxdoInterLockGetOutport Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lInterLockNo As Long, ByRef lpDstModuleNo As Long, ByRef upDstBitOffset As Long, ByRef lpSrcModuleNo As Long, ByRef upSrcBitOffset As Long, ByRef upSrcPortType As Long, ByRef upSrcCondition As Long, ByRef upOutputMode As Long, ByRef upOutputModeData As Long) As Long
    Public Declare Function AxdoInterLockIsEnabled Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lInterLockNo As Long, ByRef upEnabled As Long) As Long
    Public Declare Function AxdoInterLockResetOutport Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lInterLockNo As Long) As Long


