//=========================================
// ECE 3221 CODE25 Reader - R.Tervo 2016
//=========================================
// requires barcode wand on DE2 PS2 port
//=========================================
//=========================================
// global pointers to DE2 Board I/O ports
volatile unsigned int *leds = (unsigned int *) 0x8880;
volatile unsigned int *hexdisplay = (unsigned int *) 0x88A0;
volatile unsigned int *hexcontrol = (unsigned int *) 0x88B0;
volatile unsigned int *ps2 = (unsigned int *) 0x88F0;

volatile int *MONITOR = (char *)0x00008840;
volatile int *WAVAIL = (int *)0x00008844;
//=================================================
// this program reads the barcode wand and
// display the width (time) of the most
// recent two bars together as white:black
// on the hex display. The total number of
// black bars counted appears on the LEDs.
//=================================================
main( ){
  int whitetime, blacktime, count = 0;
  double ratio;

  *hexcontrol = 0x01FF; // enable hex display with 8 digits
  *hexdisplay = 0x0000; // initial hex display value

  char bars[100];
  char tmp;

  char lookup[10] = {6, 17, 9, 24, 5, 20, 12, 3, 18, 10};

  while(1) {
	count = 0;
    do {
      while( (*ps2 & 0x10) ){ }; // wait for ps2 LOW
      whitetime = *ps2 >> 8; // read the white bar time / 16
      while( !(*ps2 & 0x10)){ }; // wait for ps2 HIGH
      blacktime = *ps2 >> 8; // read the black bar time / 16

	  ratio = ((double)blacktime)/whitetime;
	  if(ratio > 1.5) {
		  outchar('1');
		  bars[count] = 1;
	  } else {
		  outchar('0');
		  bars[count] = 0;
	  }

      *hexdisplay = (whitetime << 16) | blacktime; // update white:black display
	  count++;
    } while(whitetime < 0x1000);
    outchar('\n');

	int index = 2, i, j, k;
	for(i = 0; i < (count-6)/5; i++) {
		tmp = 0;
		int ans = -1;
		for(j = 0; j < 5; j++) {
			tmp += bars[index] << 4-j;
			index++;
		}


		for(k = 0; k < 10; k++){
			if(tmp == lookup[k]){
				ans = k;
				break;
			}
		}

		outchar('0' + ans);
	}
	outchar('\n');
  }
}

void outchar( char ch ) {
  int buffer;
  do {
    buffer = *WAVAIL;
    buffer &= 0xFFFF0000;
  } while(!buffer);

  *MONITOR = ch;
}

void outint( char ch ) {
  int buffer;
  do {
    buffer = *WAVAIL;
    buffer &= 0xFFFF0000;
  } while(!buffer);

  *MONITOR = ch;
}
