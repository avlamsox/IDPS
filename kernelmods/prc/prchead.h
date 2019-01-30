
#define PRCMON_REFRESH_TL 0x01
#define PRCMON_GET_PROC 0x02

struct process_data {
	unsigned char process_name[64];
	void *process_handle;
}process_data;
