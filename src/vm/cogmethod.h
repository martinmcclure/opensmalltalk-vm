/* Automatically generated by
	CCodeGenerator VMMaker.oscog-eem.724 uuid: 30e942d9-0d06-42d3-8f9a-893dbdee37c2
 */

typedef struct {
	unsigned short	homeOffset;
	unsigned short	startpc;
	unsigned		cmNumArgs : 8;
	unsigned		cmType : 3;
	unsigned		cmRefersToYoung : 1;
	unsigned		cpicHasMNUCase : 1;
	unsigned		cmUsageCount : 3;
	unsigned		cmUsesPenultimateLit : 1;
	unsigned		cmUsesMethodClass : 1;
	unsigned		cmUnusedFlags : 2;
	unsigned		stackCheckOffset : 12;
 } CogBlockMethod;

typedef struct {
	sqInt	objectHeader;
	unsigned		cmNumArgs : 8;
	unsigned		cmType : 3;
	unsigned		cmRefersToYoung : 1;
	unsigned		cpicHasMNUCase : 1;
	unsigned		cmUsageCount : 3;
	unsigned		cmUsesPenultimateLit : 1;
	unsigned		cmUsesMethodClass : 1;
	unsigned		cmUnusedFlags : 2;
	unsigned		stackCheckOffset : 12;
	unsigned short	blockSize;
	unsigned short	blockEntryOffset;
	sqInt	methodObject;
	sqInt	methodHeader;
	sqInt	selector;
 } CogMethod;
