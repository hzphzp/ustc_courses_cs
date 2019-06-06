#include <cstdio>
#include <cstdlib>

unsigned char Memory[4096];
unsigned char Disk[4096];
int PDBR = 0xd80;

int LookUpPageDirectory(int PDI) {
	return (Memory[PDI + PDBR]);
}

int LookUpPageTable(int PTA,int PTI) {
	return (Memory[(PTA << 5) + PTI]);
}

int LookUpDisk(int PTA, int PTI) {
	return (Disk[(PTA << 5) + PTI]);
}

int quary(int VA) {
	printf("Virtual Address %04x:\n",VA);
	int PDI = (VA >> 10); // page directory index
	int PTI = ((VA >> 5) & 31);
	int PA = (VA & 31);
	int address, content;
	int PTA = LookUpPageDirectory(PDI);
	printf("pde index:%02x pde contents:(%02x, valid %d, pfn %02x)\n", PDI, PTA, (PTA & 128) >> 7, PTA & 127);
	if ((PTA & 128) == 0) {
		puts("Fault (page directory entry not valid)");
		return 0;
	}
	PTA = (PTA & 127);
	int PI = LookUpPageTable(PTA,PTI);
	printf("pte index:%02x pte contents:(%02x, valid %d, pfn %02x)\n", PTI, PI, (PI & 128) >> 7, PI & 127);
	if ((PI & 128) == 0) {
		if((PI & 127) == 0x7f) {
			puts("Fault (page table entry not valid)");
			return 0;
		}
		else {
			content = LookUpDisk(PI & 127, PA);
			address = (PI << 5) + PA;
			printf("To Disk Sector Address %03x --> Value: %x\n",address, content);
			return 0;
		}
		//return 0;
	}
	PI = (PI & 127);
	address = (PI << 5) + PA;
	content = Memory[address];
	printf("to Physical Address %03x --> Value: %x\n",address, content);
	return 0;
}

int main() {
	FILE *fm, *fd;
	fm = fopen("/Users/ZhengYukun/Documents/ClionProjects/L8/memory","r");
	fd = fopen("/Users/ZhengYukun/Documents/ClionProjects/L8/disk", "r");

	for (int i = 0;i < 4096;i++) {
		int a;
		fscanf(fm, "%x", &a);
		Memory[i] = a;
	}
	for (int i = 0;i < 4096;i++) {
		int a;
		fscanf(fd, "%x", &a);
		Disk[i] = a;
	}

	while (1) {
		int q;
		scanf("%x", &q);
		quary(q);
	}
	fclose(fm);
	fclose(fd);
	return 0;
}
