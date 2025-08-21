#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

int nstar, core, nframes, narmPS, nomPS, nchain, lchain;
int sls=19;
int slm=18;
int sle=20;
int newmon=100;
char **p;
void print_help()
{
	printf ("usage:re [options]\n \
	options:\n \
        -n number of new monomers\n \
	-h help\n");
	exit(1);
}

int parse_options (int argc, char *argv[])
{
	if (argc==1) print_help();
	while (--argc && (*++argv)[0] == '-') 
	{
		char c;
		c = *++argv[0];
		switch (c) 
		{
			case 'n':
				newmon=atoi(*++argv);
				break;
			case 'h' :
				print_help();
				break;
			default:
				printf ("msd: input, help:-h\n", argv[0]);
				exit (1);
		
		}
		--argc;
	}
	return 0;
}
int main(int argc, char *argv[]){
	// initialize
	double x,y,z,*xA,*yA,*zA,xB,yB,zB,xlast,ylast,zlast;
	FILE *init,*out1;
	int  n,nlast,l,b,o,i,j,k,a,c,*nmol,*natom,s;
        char outname[150];
        char buf[100]; 
	char **string_array;
        double boxx,boxy,boxz;
        double dx,dy,dz,bx,by,bz;
        char tmp1[5];
        parse_options (argc, argv);
          if((init=fopen("3mer.gro","r"))==NULL){
           printf("file can not be opened\n");
           return 1;
           } 
          
          int N_all=sls+sle+(newmon-2)*slm;
          xA=(double*)malloc((slm)*sizeof(double));
          yA=(double*)malloc((slm)*sizeof(double));
          zA=(double*)malloc((slm)*sizeof(double));
         for(i=0;i<slm;i++){
         xA[i]=yA[i]=zA[i]=0.0;
         }
         
         sprintf(outname,"%dmer.gro",newmon);
         out1=fopen(outname,"w");
         
       fprintf(out1,"PCL%dmer\n",newmon); 
       fprintf(out1,"%d\n",N_all); 
        fgets(buf,sizeof(buf),init);
        fgets(buf,sizeof(buf),init);
            
     nmol=(int*)malloc(N_all*sizeof(int));
     natom=(int*)malloc(N_all*sizeof(int));
     string_array=(char**)malloc(N_all*sizeof(char*));
       for(i=0;i<N_all;i++){
        string_array[i]=(char*)malloc(5*sizeof(char));
        nmol[i]=natom[i]=0;
        }
       //read whole star (core and arms)
        n=1; 
        a=0;   
         for(i=0;i<sls;i++){
               fscanf(init,"%5d%5c%5c%5d%lf%lf%lf",&nmol[n],&tmp1[0],string_array[n],&natom[n],&x,&y,&z);
               fprintf(out1,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",a+1,"PCL",string_array[n],n,x,y,z); 
               n++;
               }
           for(i=0;i<slm;i++){
               fscanf(init,"%5d%5c%5c%5d%lf%lf%lf",&nmol[n],&tmp1[0],string_array[i],&natom[n],&x,&y,&z);
               xA[i]=x;
               yA[i]=y;
               zA[i]=z;
               fprintf(out1,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",a+1,"PCL",string_array[i],n,x,y,z); 
               n++;
               }
	 //save the next atom    
               fscanf(init,"%5d%5c%5c%5d%lf%lf%lf",&nmol[n],&tmp1[0],string_array[n],&natom[n],&x,&y,&z);
               nlast=n;
               xB=x;
               yB=y;
               zB=z;
               xlast=x;
               ylast=y;
               zlast=z; 
               dx=xB-xA[0];
               dy=yB-yA[0];
               dz=zB-zA[0];
               bx=xB-xA[slm-3];
               by=yB-yA[slm-3];
               bz=zB-zA[slm-3];
          for(j=0;j<(newmon-3);j++){
            for(i=0;i<(slm);i++){
               fprintf(out1,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",a+1,"PCL",string_array[i],n,xA[i]+dx,yA[i]+dy,zA[i]+dz); 
               if(i==slm-1){
	       xB=xA[i]+dx+bx; 
	       yB=yA[i]+dy+by; 
	       zB=zA[i]+dz+bz; 
               dx=xB-xA[0];
               dy=yB-yA[0];
               dz=zB-zA[0];
	       }
	       n++;
               }
	   }
           //last monomer    
	     fprintf(out1,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",a+1,"PCL",string_array[nlast],n,xB,yB,zB); 
	     nlast++;
             n++;
             dx=xB-xlast;
             dy=yB-ylast;
             dz=zB-zlast;
           for(i=1;i<sle;i++){
               fscanf(init,"%5d%5c%5c%5d%lf%lf%lf",&nmol[n],&tmp1[0],string_array[nlast],&natom[nlast],&x,&y,&z);
               fprintf(out1,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",a+1,"PCL",string_array[nlast],n,x+dx,y+dy,z+dz); 
               nlast++;
               n++;
            } 
          for(i=0;i<N_all;i++){
              free(string_array[i]);
           }
           free(string_array);
           free(natom); 
           free(nmol); 
        fscanf(init,"%lf%lf%lf",&boxx,&boxy,&boxz);
         fprintf(out1,"%8.3f%8.3f%8.3f\n",boxx,boxy,boxz); 
        fgets(buf,sizeof(buf),init);
 
//end of reading all the frames
fclose(init);
fclose(out1);

return 0;
}


