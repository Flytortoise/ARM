    AREA Init ,CODE ,READONLY
	PRESERVE8
	IMPORT  |Image$$ER_ROM1$$RO$$Limit| 
    IMPORT  |Image$$RW_RAM1$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$RW_RAM1$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$RW_RAM1$$ZI$$Limit|  ; to zero initialise
	ENTRY
	
	b reset
	b halt
	b halt
	b halt
	b halt
	b halt
	b _irq
	b halt
		
reset
	ldr sp,= (0x32000000+0x100000)
	;close watchdog
    LDR R0, = 0x53000000
	LDR R1, = 0x0
	STR R1, [R0]
	
	mov r0, #0x53
	msr CPSR_cxsf, r0
	
	ldr	r0, TopOfROM
	ldr	r2, BaseOfBSS
	ldr	r3, BaseOfZero	
0
	cmp	r2, r3
	ldrcc	r1, [r0], #4
	strcc	r1, [r2], #4
	bcc	%B0	

	mov	r0,	#0
	ldr	r3,	EndOfBSS
1	
	cmp	r2,	r3
	strcc	r0, [r2], #4
	bcc	%B1
	
	; IMPORT clock_init
	; bl clock_init
	
	IMPORT Main
	bl Main

_irq
	ldr sp, =(0x31000000+0x100000)
	stmdb sp!, {r0-r12, lr}
	IMPORT do_irq 
	bl do_irq
	ldmia sp!, {r0-r12, pc}^

halt
	b halt


TopOfROM	DCD	|Image$$ER_ROM1$$RO$$Limit|
BaseOfBSS	DCD	|Image$$RW_RAM1$$RW$$Base|
BaseOfZero	DCD	|Image$$RW_RAM1$$ZI$$Base|
EndOfBSS	DCD	|Image$$RW_RAM1$$ZI$$Limit|  
	
	
	END
	
	
	
	