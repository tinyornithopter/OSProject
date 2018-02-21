void printf(char* str) //Because c library not included outside of OS we create our own simple printf function
{
	unsigned short* VideoMemory = (unsigned short*)0xb8000;//Whatever is written at 0xb8000 in memory is written straight to the graphics card (screen)
	 for(int i = 0; str[i] != '\0'; ++i)
	 	VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];//We need to divide the high and low bits because the high bit is used to decide the color information of the character/background and the low bit is used to decide on which character
}

extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
	printf("Hello World");
	while(1);//keep kernel running
}