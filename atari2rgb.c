/*--------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------*/
void atari2rgb(const char *fin, const char *fout, const unsigned char *pal)
{
	unsigned int i,j;
    FILE *fi,*fo;
    fi=fopen(fin,"rb");
    if (fi)
    {
		fseek(fi,0,SEEK_END);
		j=ftell(fi);
		fseek(fi,0,0);
		fo=fopen(fout,"w");
		if (fo)
		{
			for (i=0; i<j; i++)
			{
				unsigned char p,r,g,b;
				p=getc(fi);
				r=pal[3*p+0];
				g=pal[3*p+1];
				b=pal[3*p+2];
				putc(r,fo);
				putc(g,fo);
				putc(b,fo);
			};
			fclose(fo);
		}
		fclose(fi);
	};
}
/*--------------------------------------------------------------------*/
void loadpal(const char *fin, unsigned char *pal)
{
	FILE *fi;
	fi=fopen(fin,"rb");
	if (fi)
	{
		fread(pal,sizeof(unsigned char),3*256,fi);
		fclose(fi);
	};
}
/*--------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	unsigned char pal[3*256];
	switch (argc)
	{
		case 4:
		{
			loadpal(argv[1],pal);
			atari2rgb(argv[2],argv[3],pal);
		} break;
		default:
		{
			printf("ATARI2RGB - Convert ATARI-PAL to RGB-RAW - (c)GienekP\n");
			printf("use:\n");
			printf("   atari2rgb pal.act filein.atari fileout.rgb\n");	
		} break;
	};
	return 0;
}
/*--------------------------------------------------------------------*/
