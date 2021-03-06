
#define SCREEN_XDIM 132
#define SCREEN_YDIM 132

void FbInit(void);
void plot_point(int x, int y, void *context);
void FbSwapBuffers(void);
void FbPushBuffer(void);
void FbLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void FbHorizontalLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void FbVerticalLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void FbClear(void);
void FbMove(unsigned char x, unsigned char y);
void FbWriteLine(char *s);
void itoa(char *string, int value, int base);
int abs(int x);
void returnToMenus(void);
void FbColor(int color);
void setNote(int note, int duration);

/* Port numbers are in host byte order here. UDP is used if serial_port is NULL, otherwise serial port is used */
void setup_linux_ir_simulator(char *serial_port, unsigned short port_to_recv_from, unsigned short port_to_xmit_on);

void disable_interrupts(void);
void enable_interrupts(void);
void start_gtk(int *argc, char ***argv, int (*main_badge_function)(void), int callback_hz);

#define BLUE    0
#define GREEN   1
#define RED     2
#define BLACK   3
#define WHITE   4
#define CYAN    5
#define YELLOW  6
#define MAGENTA 7

int button_pressed_and_consume();
int up_btn_and_consume();
int down_btn_and_consume();
int left_btn_and_consume();
int right_btn_and_consume();

/* Emulate some stuff from ir.c */
extern int IRpacketOutNext;
extern int IRpacketOutCurr;
#define MAXPACKETQUEUE 16
#define IR_OUTPUT_QUEUE_FULL (((IRpacketOutNext+1) % MAXPACKETQUEUE) == IRpacketOutCurr)

#define BUTTON_PRESSED_AND_CONSUME button_pressed_and_consume()
#define DOWN_BTN_AND_CONSUME down_btn_and_consume()
#define UP_BTN_AND_CONSUME up_btn_and_consume()
#define LEFT_BTN_AND_CONSUME left_btn_and_consume()
#define RIGHT_BTN_AND_CONSUME right_btn_and_consume()

struct IRpacket_t {
	/* Note: this is different than what the badge code actually uses.
	 * The badge code uses 32-bits worth of bitfields.  Bitfields are
	 * not portable, nor are they clear, and *which* particular bits
	 * any bitfields land in are completely up to the compiler.
	 * Relying on the compiler using any particular bits is a programming
	 * error, so don't actually use this. Instead always
	 * use the "v" element of the IRpacket_u union.
	 */
	unsigned int v;
};

union IRpacket_u {
	struct IRpacket_t p;
	unsigned int v;
};

extern struct sysData_t {
	unsigned short badgeId;
} G_sysData;

void IRqueueSend(union IRpacket_u pkt);

/* This is tentative.  Not really sure how the IR stuff works.
   For now, I will assume I register a callback to receive 32-bit
   packets incoming from IR sensor. */
void register_ir_packet_callback(void (*callback)(struct IRpacket_t));
void unregister_ir_packet_callback(void);

void flareled(unsigned char r, unsigned char g, unsigned char b);

#define IR_APP1 19
#define IR_APP2 20
#define IR_APP3 21
#define IR_APP4 22
#define IR_APP5 23
#define IR_APP6 24
#define IR_APP7 25

extern char username[10];
