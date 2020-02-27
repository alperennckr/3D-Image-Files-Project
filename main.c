#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
DIR *klasor;
struct dirent *giris;
struct noktalar
{
    float x,y,z;
};
struct noktalarr
{
    float x,y,z;
    int r,g,b;
};
int kontrol(FILE *dosya,FILE *dosya1)
{
    char bilgi[200],tut[10][100],oyle[100],tip[100];
    int satir=0,sayi=0,alan=0,sayac=0,uzunluk,flag,hata=0;
    char noktasayisi[100],gecici[10]="xyz",gecici2[10]="xyzrgb";
    int as=0,k;
    char *ch;
    while(fgets(bilgi,"%s",dosya)!=NULL)
    {
        satir++;
        if(satir<6)
        {
            uzunluk=strlen(bilgi);
            strcpy(tut[sayac],bilgi);
            sayac++;
            tut[sayac-1][uzunluk-1]='\0';
        }
        if(satir==1)
        {
            if(strcmp(tut[sayac-1],"# Noktalar dosya format")!=0)
            {
                printf("Format yanlis verilmistir\n");
                fputs("Format yanlis verilmistir.\n",dosya1);
                return 0;
            }
        }
        if(satir==2)
        {
            if(strcmp(tut[sayac-1],"VERSION 1")!=0)
            {
                printf("Versiyon yanlis verilmistir\n");
                fputs("Versiyon yanlis verilmistir\n",dosya1);
                return 0;
            }
        }
        if(satir==3)
        {
            if(strcmp(tut[sayac-1],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[sayac-1],"ALANLAR x y z")==0)
            {
                alan=3;
            }
            else
            {
                printf("Alan bilgisi hatali verilmistir\n");
                fputs("Alan bilgisi hatali verilmistir\n",dosya1);
                return 0;
            }
        }
        if(satir==4)
        {
            sscanf(tut[sayac-1],"%s%s",&oyle,&noktasayisi);
            flag=atoi(noktasayisi);
        }
        if(satir==5)
        {
            sscanf(tut[sayac-1],"%s%s",&oyle,&tip);
            if(strcmp(tip,"binary")==0)
            {
                return 2;
            }
        }
        if(satir>5)
        {
            ch = strtok (bilgi," ");
            while (ch != NULL)
            {
                as++;
                ch = strtok (NULL," ");
            }
            if(alan==6&&as!=6 && alan!=0)
            {
                printf("%d. nokta verisi ",(sayi+1));
                fprintf(dosya1,"%d. nokta verisi ",(sayi+1));
                for(k=as; k<6; k++)
                {
                    printf("%c ",gecici2[k]);
                    fprintf(dosya1,"%c ",gecici2[k]);
                    hata++;
                }
                printf("bilgisi olmadan verilmistir.\n");
                fputs("bilgisi olmadan verilmistir.\n",dosya1);
                return 0;
            }
            else if(alan==3&&as!=3 && alan!=0)
            {
                printf("%d. nokta verisi ",(sayi+1));
                fprintf(dosya1,"%d. nokta verisi ",(sayi+1));
                for(k=as; k<3; k++)
                {
                    printf("%c ",gecici[k]);
                    fprintf(dosya1,"%c ",gecici[k]);
                    hata++;
                }
                printf("bilgisi olmadan verilmistir.\n");
                fputs("bilgisi olmadan verilmistir.\n",dosya1);
                return 0;
            }
            sayi++;
            as=0;
        }
    }
    if(flag==(sayi-hata))
    {
        printf("Butun veriler uyumludur.\n");
        fputs("Butun veriler uyumludur.\n",dosya1);
    }
   else if(flag!=(sayi-hata))
    {
        printf("Nokta sayisi yanlistir.\n");
        fputs("Nokta sayisi yanlistir.\n",dosya1);
        return 0;
    }
}
int kontrolb(FILE *dosya,FILE *dosya1)
{
    int sayac=0,uzunluk,i,alan,flag;
    struct noktalar nokta[10000];
    struct noktalarr noktar[10000];
    char bilgi[200],tut[10][100],oyle[50],sayi[100],gecici[5]="xyz",gecici2[10]="xyzrgb";
    for(i=0; i<5; i++)
    {
        fgets(bilgi,200,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[sayac],bilgi);
        sayac++;
        tut[sayac-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
        if(i==3)
        {
            sscanf(tut[i],"%s%s",&oyle,&sayi);
            flag=atoi(sayi);
        }
    }
    i=0;
    int k=0,j;
    for(j=0; j<flag; i++)
    {
        if(alan==6)
        {
            for(j=0; j<flag; j++)
            {
                noktar[k].x=-1;
                noktar[k].y=-1;
                noktar[k].z=-1;
                noktar[k].r=-1;
                noktar[k].g=-1;
                noktar[k].b=-1;
                k++;
            }
        }
        if(alan==3)
        {
            for(j=0; j<flag; j++)
            {
                nokta[k].x=-1;
                nokta[k].y=-1;
                nokta[k].z=-1;
                k++;
            }
        }
    }
    while(i<flag)
    {
        if(alan==3)
            fread(nokta,sizeof(nokta),1,dosya);
        else if(alan==6)
            fread(noktar,sizeof(noktar),1,dosya);
        i++;
    }
    int bnsay=0,g;
    if(alan==3)
    {
        bnsay++;
        for(j=0; j<flag; j++)
        {
            if(nokta[j].x==-1 && nokta[j].y==-1 && nokta[j].z)
            {
                for(g=bnsay; g<3; g++)
                {
                    printf("%c ",gecici[g]);
                    return 0;
                }
            }
        }
        bnsay=0;
    }
    if(alan==6)
    {
        bnsay++;
        for(j=0; j<flag; j++)
        {
            if(noktar[j].x==-1 && noktar[j].y==-1 && noktar[j].r==-1 && noktar[j].g==-1 && noktar[j].b==-1)
            {
                for(g=bnsay; g<6; g++)
                {
                    printf("%c ",gecici[g]);
                    return 0;
                }
            }
        }
        bnsay=0;
    }
    printf("Butun veriler uyumludur.\n");
    fputs("Butun veriler uyumludur.\n",dosya1);
}
void yakinuzak(FILE *dosya,FILE *dosya1)
{
    fputs("EN YAKIN/UZAK NOKTALAR: \n",dosya1);
    char bilgi[200],x[50],y[50],z[50],r[50],g[50],b[50],tut[10][100];
    int sayac=0,satir=0,i,j,k=0,kr=0,alan,uzunluk;
    struct noktalar *nokta=malloc(sizeof(struct noktalar) * (k+1));
    struct noktalarr *noktar=malloc(sizeof(struct noktalarr) * (kr+1));
    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[satir],bilgi);
        satir++;
        tut[satir-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
    }
    while (fgets(bilgi,200,dosya)!= NULL)
    {
        if(alan==6)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s%s%s%s",x,y,z,r,g,b);
                noktar[sayac].x=atof(x);
                noktar[sayac].y=atof(y);
                noktar[sayac].z=atof(z);
                noktar[sayac].r=atof(r);
                noktar[sayac].g=atof(g);
                noktar[sayac].b=atof(b);
                sayac++;
            }
            noktar=realloc(noktar,sizeof(struct noktalarr)*(sayac+1));
        }
        if(alan==3)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s",x,y,z);
                nokta[sayac].x=atof(x);
                nokta[sayac].y=atof(y);
                nokta[sayac].z=atof(z);
                sayac++;
            }
            nokta=realloc(nokta,sizeof(struct noktalar)*(sayac+1));
        }
    }
    if(alan==3)
    {
        float enbuyuk=sqrt((pow((nokta[0].x-nokta[1].x),2))+(pow((nokta[0].y-nokta[1].y),2))+(pow((nokta[0].z-nokta[1].z),2)));
        float enkucuk=sqrt((pow((nokta[0].x-nokta[1].x),2))+(pow((nokta[0].y-nokta[1].y),2))+(pow((nokta[0].z-nokta[1].z),2)));
        float tempk,tempb;
        int satirk1,satirk2,satirb1,satirb2;
        for(i=0; i<sayac; i++)
        {
            for(j=1; j<sayac; j++)
            {
                tempk=sqrt((pow((nokta[i].x-nokta[j].x),2))+(pow((nokta[i].y-nokta[j].y),2))+(pow((nokta[i].z-nokta[j].z),2)));
                tempb=sqrt((pow((nokta[i].x-nokta[j].x),2))+(pow((nokta[i].y-nokta[j].y),2))+(pow((nokta[i].z-nokta[j].z),2)));
                if(tempk<enkucuk && i!=j)
                {
                    enkucuk=tempk;
                    satirk1=i;
                    satirk2=j;
                }
                if(tempb>enbuyuk)
                {
                    enbuyuk=tempb;
                    satirb1=i;
                    satirb2=j;
                }
            }
        }

        printf("En uzak iki nokta :\n");
        fputs("En uzak iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirb1+1,nokta[satirb1].x,nokta[satirb1].y,nokta[satirb1].z);
        fprintf(dosya1,"%d. satir nokta:%f %f %f\n",satirb1+1,nokta[satirb1].x,nokta[satirb1].y,nokta[satirb1].z);
        printf("%d. satir nokta:%f %f %f\n",satirb2+1,nokta[satirb2].x,nokta[satirb2].y,nokta[satirb2].z);
        fprintf(dosya1,"%d. satir nokta:%f %f %f\n",satirb2+1,nokta[satirb2].x,nokta[satirb2].y,nokta[satirb2].z);
        printf("Aradaki mesafe: %f\n",enbuyuk);
        fprintf(dosya1,"Aradaki mesafe: %f\n",enbuyuk);
        printf("En yakin iki nokta :\n");
        fputs("En yakin iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirk1+1,nokta[satirk1].x,nokta[satirk1].y,nokta[satirk1].z);
        fprintf(dosya1,"%d. satir nokta:%f %f %f\n",satirk1+1,nokta[satirk1].x,nokta[satirk1].y,nokta[satirk1].z);
        printf("%d. satir nokta:%f %f %f\n",satirk2+1,nokta[satirk2].x,nokta[satirk2].y,nokta[satirk2].z);
        fprintf(dosya1,"%d. satir nokta:%f %f %f\n",satirk2+1,nokta[satirk2].x,nokta[satirk2].y,nokta[satirk2].z);
        printf("Aradaki mesafe: %f\n",enkucuk);
        fprintf(dosya1,"Aradaki mesafe: %f\n",enkucuk);
    }
    if(alan==6)
    {
        float enbuyuk=sqrt((pow((noktar[0].x-noktar[1].x),2))+(pow((noktar[0].y-noktar[1].y),2))+(pow((noktar[0].z-noktar[1].z),2)));
        float enkucuk=sqrt((pow((noktar[0].x-noktar[1].x),2))+(pow((noktar[0].y-noktar[1].y),2))+(pow((noktar[0].z-noktar[1].z),2)));
        float tempk,tempb;
        int satirk1,satirk2,satirb1,satirb2;
        for(i=0; i<sayac; i++)
        {
            for(j=1; j<sayac; j++)
            {
                tempk=sqrt((pow((noktar[i].x-noktar[j].x),2))+(pow((noktar[i].y-noktar[j].y),2))+(pow((noktar[i].z-noktar[j].z),2)));
                tempb=sqrt((pow((noktar[i].x-noktar[j].x),2))+(pow((noktar[i].y-noktar[j].y),2))+(pow((noktar[i].z-noktar[j].z),2)));
                if(tempk<enkucuk && i!=j)
                {
                    enkucuk=tempk;
                    satirk1=i;
                    satirk2=j;
                }
                if(tempb>enbuyuk)
                {
                    enbuyuk=tempb;
                    satirb1=i;
                    satirb2=j;
                }
            }
        }
        printf("En uzak iki nokta :\n");
        fputs("En uzak iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirb1+1,noktar[satirb1].x,noktar[satirb1].y,noktar[satirb1].z,noktar[satirb1].r,noktar[satirb1].g,noktar[satirb1].b);
        fprintf(dosya1,"%d. satir nokta:%f %f %f %d %d %d\n",satirb1+1,noktar[satirb1].x,noktar[satirb1].y,noktar[satirb1].z,noktar[satirb1].r,noktar[satirb1].g,noktar[satirb1].b);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirb2+1,noktar[satirb2].x,noktar[satirb2].y,noktar[satirb2].z,noktar[satirb2].r,noktar[satirb2].g,noktar[satirb2].b);
        fprintf(dosya1,"%d. satir nokta:%f %f %f %d %d %d\n",satirb2+1,noktar[satirb2].x,noktar[satirb2].y,noktar[satirb2].z,noktar[satirb2].r,noktar[satirb2].g,noktar[satirb2].b);
        printf("Aradaki mesafe: %f\n",enbuyuk);
        fprintf(dosya1,"Aradaki mesafe: %f\n",enbuyuk);
        printf("En yakin iki nokta :\n");
        fputs("En yakin iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirk1+1,noktar[satirk1].x,noktar[satirk1].y,noktar[satirk1].z,noktar[satirk1].r,noktar[satirk1].g,noktar[satirk1].b);
        fprintf(dosya1,"%d. satir nokta:%f %f %f %d %d %d\n",satirk1+1,noktar[satirk1].x,noktar[satirk1].y,noktar[satirk1].z,noktar[satirk1].r,noktar[satirk1].g,noktar[satirk1].b);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirk2+1,noktar[satirk2].x,noktar[satirk2].y,noktar[satirk2].z,noktar[satirk2].r,noktar[satirk2].g,noktar[satirk2].b);
        fprintf(dosya1,"%d. satir nokta:%f %f %f %d %d %d\n",satirk2+1,noktar[satirk2].x,noktar[satirk2].y,noktar[satirk2].z,noktar[satirk2].r,noktar[satirk2].g,noktar[satirk2].b);
        printf("Aradaki mesafe: %f\n",enkucuk);
        fprintf(dosya1,"Aradaki mesafe: %f\n",enkucuk);
    }
}
void yakinuzakb(FILE *dosya,FILE *dosya1)
{
    fputs("\nEN YAKIN/UZAK NOKTALAR: \n",dosya1);
    struct noktalar nokta[1000];
    struct noktalarr noktar[1000];
    int i=0,j,t,alan,uzunluk,sayac=0,flag;
    char bilgi[200],oyle[10],sayi[10],tut[10][100];

    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[sayac],bilgi);
        sayac++;
        tut[sayac-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
        if(i==3)
        {
            sscanf(tut[i],"%s%s",&oyle,&sayi);
            flag=atoi(sayi);
        }
    }
    i=0;
    while(i<flag)
    {
        if(alan==3)
            fread(nokta,sizeof(nokta),1,dosya);
        else if(alan==6)
            fread(noktar,sizeof(noktar),1,dosya);
        i++;
    }

    if(alan==3)
    {
        float enbuyuk=sqrt((pow((nokta[0].x-nokta[1].x),2))+(pow((nokta[0].y-nokta[1].y),2))+(pow((nokta[0].z-nokta[1].z),2)));
        float enkucuk=sqrt((pow((nokta[0].x-nokta[1].x),2))+(pow((nokta[0].y-nokta[1].y),2))+(pow((nokta[0].z-nokta[1].z),2)));
        float tempk,tempb;
        int satirk1,satirk2,satirb1,satirb2;
        for(t=0; t<flag; t++)
        {
            for(j=1; j<flag; j++)
            {
                tempk=sqrt((pow((nokta[t].x-nokta[j].x),2))+(pow((nokta[t].y-nokta[j].y),2))+(pow((nokta[t].z-nokta[j].z),2)));
                tempb=sqrt((pow((nokta[t].x-nokta[j].x),2))+(pow((nokta[t].y-nokta[j].y),2))+(pow((nokta[t].z-nokta[j].z),2)));
                if(tempk<enkucuk && t!=j)
                {
                    enkucuk=tempk;
                    satirk1=t;
                    satirk2=j;
                }
                if(tempb>enbuyuk)
                {
                    enbuyuk=tempb;
                    satirb1=t;
                    satirb2=j;
                }
            }
        }
        printf("En uzak iki nokta :\n");
        fputs("\nEn uzak iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirb1+1,nokta[satirb1].x,nokta[satirb1].y,nokta[satirb1].z);
        fwrite(&nokta[satirb1],sizeof(struct noktalar),1,dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirb2+1,nokta[satirb2].x,nokta[satirb2].y,nokta[satirb2].z);
        fwrite(&nokta[satirb2],sizeof(struct noktalar),1,dosya1);
        printf("Aradaki mesafe: %f\n",enbuyuk);
        fwrite(&enbuyuk,sizeof(float),1,dosya1);
        printf("En yakin iki nokta :\n");
        fputs("\nEn yakin iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirk1+1,nokta[satirk1].x,nokta[satirk1].y,nokta[satirk1].z);
        fwrite(&nokta[satirk1],sizeof(struct noktalar),1,dosya1);
        printf("%d. satir nokta:%f %f %f\n",satirk2+1,nokta[satirk2].x,nokta[satirk2].y,nokta[satirk2].z);
        fwrite(&nokta[satirk2],sizeof(struct noktalar),1,dosya1);
        printf("Aradaki mesafe: %f\n",enkucuk);
        fwrite(&enkucuk,sizeof(float),1,dosya1);
    }

    else if(alan==6)
    {
        float enbuyuk=sqrt((pow((noktar[0].x-noktar[1].x),2))+(pow((noktar[0].y-noktar[1].y),2))+(pow((noktar[0].z-noktar[1].z),2)));
        float enkucuk=sqrt((pow((noktar[0].x-noktar[1].x),2))+(pow((noktar[0].y-noktar[1].y),2))+(pow((noktar[0].z-noktar[1].z),2)));
        float tempk,tempb;
        int satirk1,satirk2,satirb1,satirb2;
        for(t=0; t<flag; t++)
        {
            for(j=1; j<flag; j++)
            {
                tempk=sqrt((pow((noktar[t].x-noktar[j].x),2))+(pow((noktar[t].y-noktar[j].y),2))+(pow((noktar[t].z-noktar[j].z),2)));
                tempb=sqrt((pow((noktar[t].x-noktar[j].x),2))+(pow((noktar[t].y-noktar[j].y),2))+(pow((noktar[t].z-noktar[j].z),2)));
                if(tempk<enkucuk && t!=j)
                {
                    enkucuk=tempk;
                    satirk1=t;
                    satirk2=j;
                }
                if(tempb>enbuyuk)
                {
                    enbuyuk=tempb;
                    satirb1=t;
                    satirb2=j;
                }
            }
        }
        printf("\nEn uzak iki nokta :\n");
        fputs("En uzak iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirb1+1,noktar[satirb1].x,noktar[satirb1].y,noktar[satirb1].z,noktar[satirb1].r,noktar[satirb1].g,noktar[satirb1].b);
        fwrite(&noktar[satirb1],sizeof(struct noktalarr),1,dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirb2+1,noktar[satirb2].x,noktar[satirb2].y,noktar[satirb2].z,noktar[satirb2].r,noktar[satirb2].g,noktar[satirb2].b);
        fwrite(&noktar[satirb2],sizeof(struct noktalarr),1,dosya1);
        printf("Aradaki mesafe: %f\n",enbuyuk);
        fwrite(&enbuyuk,sizeof(float),1,dosya1);
        printf("En yakin iki nokta :\n");
        fputs("\nEn yakin iki nokta :\n",dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirk1+1,noktar[satirk1].x,noktar[satirk1].y,noktar[satirk1].z,noktar[satirk1].r,noktar[satirk1].g,noktar[satirk1].b);
        fwrite(&noktar[satirk1],sizeof(struct noktalarr),1,dosya1);
        printf("%d. satir nokta:%f %f %f %d %d %d\n",satirk2+1,noktar[satirk2].x,noktar[satirk2].y,noktar[satirk2].z,noktar[satirk2].r,noktar[satirk2].g,noktar[satirk2].b);
        fwrite(&noktar[satirk2],sizeof(struct noktalarr),1,dosya1);
        printf("Aradaki mesafe: %f\n",enkucuk);
        fwrite(&enkucuk,sizeof(float),1,dosya1);
    }
}
void noktaortalama(FILE *dosya,FILE *dosya1)
{
    fputs("NOKTA UZAKLIKLARI: \n",dosya1);
    char bilgi[200],x[50],y[50],z[50],tut[10][100],r[50],g[50],b[50];
    int k,m,i,j,sayac=0,f=0,say=0,kr=0,uzunluk,satir=0,alan;
    struct noktalar *nokta=malloc(sizeof(struct noktalar) * (m+1));
    struct noktalarr *noktar=malloc(sizeof(struct noktalarr) * (kr+1));
    float toplam=0.0,ortalama=0.0;
    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[satir],bilgi);
        satir++;
        tut[satir-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
    }
    while (fgets(bilgi,200,dosya)!= NULL)
    {
        if(alan==6)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s%s%s%s",x,y,z,r,g,b);
                noktar[sayac].x=atof(x);
                noktar[sayac].y=atof(y);
                noktar[sayac].z=atof(z);
                noktar[sayac].r=atof(r);
                noktar[sayac].g=atof(g);
                noktar[sayac].b=atof(b);
                sayac++;
            }
            noktar=realloc(noktar,sizeof(struct noktalarr)*(sayac+1));
        }
        if(alan==3)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s",x,y,z);
                nokta[sayac].x=atof(x);
                nokta[sayac].y=atof(y);
                nokta[sayac].z=atof(z);
                sayac++;
            }
            nokta=realloc(nokta,sizeof(struct noktalar)*(sayac+1));
        }
    }
    if(alan==3)
    {
        for(k=0; k<sayac; k++)
        {
            for(j=(k+1); j<sayac; j++)
            {
                toplam+=sqrt((pow((nokta[k].x-nokta[j].x),2))+(pow((nokta[k].y-nokta[j].y),2))+(pow((nokta[k].z-nokta[j].z),2)));
                f++;
                if(f==sayac/4 || (k==sayac-1 && j==sayac-1))
                {
                    ortalama+=toplam/f;
                    say++;
                    toplam=0;
                    f=0;
                }
            }
        }
        printf("Uzaklik ortalamasi : %f \n",(ortalama/say));
        fprintf(dosya1,"Uzaklik ortalamasi : %f \n",(ortalama/say));
    }
    if(alan==6)
    {
        for(k=0; k<sayac; k++)
        {
            for(j=(k+1); j<sayac; j++)
            {
                toplam+=sqrt((pow((noktar[k].x-noktar[j].x),2))+(pow((noktar[k].y-noktar[j].y),2))+(pow((noktar[k].z-noktar[j].z),2)));
                f++;
                if(f==sayac/4 || (k==sayac-1 && j==sayac-1))
                {
                    ortalama+=toplam/f;
                    say++;
                    toplam=0;
                    f=0;
                }
            }
        }
        printf("Uzaklik ortalamasi : %f \n",(ortalama/say));
        fprintf(dosya1,"Uzaklik ortalamasi : %f \n",(ortalama/say));
    }
}
void noktaortalamab(FILE *dosya,FILE *dosya1)
{
    fputs("\nNOKTA UZAKLIKLARI: \n",dosya1);
    struct noktalar nokta[1000];
    struct noktalarr noktar[1000];
    int i=0,alan,uzunluk,sayac=0,flag;
    char bilgi[200],oyle[10],sayi[10],tut[10][100];

    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[sayac],bilgi);
        sayac++;
        tut[sayac-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
        if(i==3)
        {
            sscanf(tut[i],"%s%s",&oyle,&sayi);
            flag=atoi(sayi);
        }
    }
    i=0;
    while(i<flag)
    {
        if(alan==3)
            fread(nokta,sizeof(nokta),1,dosya);
        else if(alan==6)
            fread(noktar,sizeof(noktar),1,dosya);
        i++;
    }
    if(alan==3)
    {
        int k,j,g=0,say=0;
        float toplam=0.0,ortalama=0.0,aortalama;
        for(k=0; k<flag; k++)
        {
            for(j=(k+1); j<flag; j++)
            {
                toplam+=sqrt((pow((nokta[k].x-nokta[j].x),2))+(pow((nokta[k].y-nokta[j].y),2))+(pow((nokta[k].z-nokta[j].z),2)));
                g++;
                if(g==(flag/4) || (k==flag-1 && j==flag-1))
                {
                    ortalama+=toplam/g;
                    say++;
                    toplam=0;
                    g=0;
                }
            }
        }
        aortalama=(float)ortalama/say;
        printf("Uzaklik ortalamasi : %f \n",(ortalama/say));
        fwrite(&aortalama,sizeof(float),1,dosya1);
    }
    if(alan==6)
    {
        int k,j,g=0,say=0;
        float toplam=0.0,ortalama=0.0,aortalama;
        for(k=0; k<flag; k++)
        {
            for(j=(k+1); j<flag; j++)
            {
                toplam+=sqrt((pow((noktar[k].x-noktar[j].x),2))+(pow((noktar[k].y-nokta[j].y),2))+(pow((noktar[k].z-nokta[j].z),2)));
                g++;
                if(g==(flag/4) || (k==flag-1 && j==flag-1))
                {
                    ortalama+=toplam/g;
                    say++;
                    toplam=0;
                    g=0;
                }
            }
        }
        aortalama=(float)ortalama/say;
        printf("Uzaklik ortalamasi : %f \n",(ortalama/say));
        fwrite(&aortalama,sizeof(float),1,dosya1);
    }
}
void kure(FILE *dosya,FILE *dosya1,float *xk,float *yk,float *zk,float *yr)
{

    fputs("KURE BILGILERI: \n",dosya1);
    int m=0,k,kr=0,sayac=0,i,alan,satir=0,uzunluk;
    struct noktalar nokta;
    struct noktalarr noktar;
    float uzaklik;
    char bilgi[200],x[50],y[50],z[50],r[50],g[50],b[50],tut[10][100];
    fprintf(dosya1,"Kullanicidan alinan kurenin x degeri:%f\n",*xk);
    fprintf(dosya1,"Kullanicidan alinan kurenin y degeri:%f\n",*yk);
    fprintf(dosya1,"Kullanicidan alinan kurenin z degeri:%f\n",*zk);
    fprintf(dosya1,"Kullanicidan alinan kurenin yaricap degeri:%f\n",*yr);
    printf("Icinde kalan noktalar: \n");
    fputs("Icinde kalan noktalar: \n",dosya1);
    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[satir],bilgi);
        satir++;
        tut[satir-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
    }

    while (fgets(bilgi,200,dosya)!= NULL)
    {
        if(alan==6)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s%s%s%s",x,y,z,r,g,b);
                noktar.x=atof(x);
                noktar.y=atof(y);
                noktar.z=atof(z);
                noktar.r=atoi(r);
                noktar.g=atoi(g);
                noktar.b=atoi(b);
                uzaklik=sqrt((pow((*xk-noktar.x),2))+(pow((*yk-noktar.y),2))+(pow((*zk-noktar.z),2)));
                if(uzaklik<*yr)
                {
                    printf("%f %f %f %d %d %d\n",noktar.x,noktar.y,noktar.z,noktar.r,noktar.g,noktar.b);
                    fprintf(dosya1,"%f %f %f %d %d %d\n",noktar.x,noktar.y,noktar.z,noktar.r,noktar.g,noktar.b);

                }

            }

        }
        if(alan==3)
        {
            if(isdigit(*bilgi))
            {
                sscanf(bilgi,"%s%s%s",x,y,z);
                nokta.x=atof(x);
                nokta.y=atof(y);
                nokta.z=atof(z);
                sayac++;
            }
            uzaklik=sqrt((pow((*xk-nokta.x),2))+(pow((*yk-nokta.y),2))+(pow((*zk-nokta.z),2)));

            if(uzaklik<=*yr)
            {
                printf("%f %f %f\n",nokta.x,nokta.y,nokta.z);
                fprintf(dosya1,"%f %f %f\n",nokta.x,nokta.y,nokta.z);

            }

        }
    }

}
void kureb(FILE *dosya,FILE *dosya1,float *xk,float *yk,float *zk,float *yr)
{
    fputs("\nKURE BILGILERI: \n",dosya1);
    struct noktalar nokta[1000];
    struct noktalarr noktar[1000];
    int i=0,alan,uzunluk,sayac=0,flag;
    char bilgi[200],oyle[10],sayi[10],tut[10][100];

    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[sayac],bilgi);
        sayac++;
        tut[sayac-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
        if(i==3)
        {
            sscanf(tut[i],"%s%s",&oyle,&sayi);
            flag=atoi(sayi);
        }
    }
    i=0;
    int k=0;
    float uzaklik;
    while(i<flag)
    {
        if(alan==3)
            fread(nokta,sizeof(nokta),1,dosya);
        else if(alan==6)
            fread(noktar,sizeof(noktar),1,dosya);
        i++;
    }
    if(alan==3)
    {
        fwrite(&xk,sizeof(float),1,dosya1);
        fwrite(&yk,sizeof(float),1,dosya1);
        fwrite(&zk,sizeof(float),1,dosya1);
        fwrite(&yr,sizeof(float),1,dosya1);
        printf("Icinde kalan noktalar: \n");
        fputs("\nIcinde kalan noktalar: \n",dosya1);
        for(k=0; k<flag; k++)
        {
            uzaklik=sqrt((pow((*xk-nokta[k].x),2))+(pow((*yk-nokta[k].y),2))+(pow((*zk-nokta[k].z),2)));
            if(uzaklik<=*yr)
            {
                printf("%f %f %f\n",nokta[k].x,nokta[k].y,nokta[k].z);
                fwrite(&nokta,sizeof(struct noktalar),1,dosya1);
            }
        }
    }
    if(alan==6)
    {
        fwrite(&xk,sizeof(float),1,dosya1);
        fwrite(&yk,sizeof(float),1,dosya1);
        fwrite(&zk,sizeof(float),1,dosya1);
        fwrite(&yr,sizeof(float),1,dosya1);

        printf("Icinde kalan noktalar: \n");
        fputs("\nIcinde kalan noktalar: \n",dosya1);
        for(k=0; k<flag; k++)
        {
            uzaklik=sqrt((pow((*xk-noktar[k].x),2))+(pow((*yk-noktar[k].y),2))+(pow((*zk-noktar[k].z),2)));
            if(uzaklik<=*yr)
            {
                printf("%f %f %f %d %d %d\n",noktar[k].x,noktar[k].y,noktar[k].z,noktar[k].r,noktar[k].g,noktar[k].b);
                fwrite(&noktar,sizeof(struct noktalarr),1,dosya1);
            }
        }
    }
}
void kup(FILE *dosya,FILE *dosya1)
{
    fputs("KUP BILGILERI: \n",dosya1);
    int k,m=0,sayac=0;
    float ekle,dizi[3];
    char bilgi[200],x[50],y[50],z[50];
    struct noktalar enbuyuk;
    struct noktalar enkucuk;
    struct noktalar *nokta=malloc(sizeof(struct noktalar) * (m+1));
    while (fgets(bilgi,200,dosya)!= NULL)
    {
        if(isdigit(*bilgi))
        {
            sscanf(bilgi,"%s%s%s",x,y,z);
            nokta[sayac].x=atof(x);
            nokta[sayac].y=atof(y);
            nokta[sayac].z=atof(z);
            sayac++;
        }
        nokta=realloc(nokta,sizeof(struct noktalar)*(sayac+1));
    }
    enbuyuk.x=nokta[0].x;
    enbuyuk.y=nokta[0].y;
    enbuyuk.z=nokta[0].z;
    enkucuk.x=nokta[0].x;
    enkucuk.y=nokta[0].y;
    enkucuk.z=nokta[0].z;
    for(k=1; k<sayac; k++)
    {
        if(nokta[k].x>enbuyuk.x)
            enbuyuk.x=nokta[k].x;

        if(nokta[k].y>enbuyuk.y)
            enbuyuk.y=nokta[k].y;

        if(nokta[k].z>enbuyuk.z)
            enbuyuk.z=nokta[k].z;

        if(nokta[k].x<enkucuk.x)
            enkucuk.x=nokta[k].x;

        if(nokta[k].y<enkucuk.y)
            enkucuk.y=nokta[k].y;

        if(nokta[k].z<enkucuk.z)
            enbuyuk.z=nokta[k].z;
    }
    dizi[0]=enbuyuk.x-enkucuk.x;
    dizi[1]=enbuyuk.y-enkucuk.y;
    dizi[2]=enbuyuk.z-enkucuk.z;
    ekle=dizi[0];
    for(k=0; k<3; k++)
    {
        if(dizi[k]>ekle)
            ekle=dizi[k];
    }
    printf("1. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z);
    fprintf(dosya1,"1. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z);
    printf("2. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z);
    fprintf(dosya1,"2. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z);
    printf("3. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z-ekle);
    fprintf(dosya1,"3. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z-ekle);
    printf("4. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z-ekle);
    fprintf(dosya1,"4. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z-ekle);
    printf("5. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z);
    fprintf(dosya1,"5. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z);
    printf("6. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z-ekle);
    fprintf(dosya1,"6. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z-ekle);
    printf("7. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z-ekle);
    fprintf(dosya1,"7. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z-ekle);
    printf("8. kose x: %f y: %f z: %f \n\n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z);
    fprintf(dosya1,"8. kose x: %f y: %f z: %f \n\n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z);
}
void kupb(FILE *dosya,FILE *dosya1)
{
    fputs("\nKUP BILGILERI: \n",dosya1);
    struct noktalar nokta[1000];
    struct noktalar islem[1000];
    struct noktalarr noktar[1000];
    int i=0,alan,uzunluk,sayac=0,flag;
    char bilgi[200],oyle[10],sayi[10],tut[10][100];

    for(i=0; i<5; i++)
    {
        fgets(bilgi,100,dosya);
        uzunluk=strlen(bilgi);
        strcpy(tut[sayac],bilgi);
        sayac++;
        tut[sayac-1][uzunluk-1]='\0';
        if(i==2)
        {
            if(strcmp(tut[i],"ALANLAR x y z r g b")==0)
            {
                alan=6;
            }
            else if(strcmp(tut[i],"ALANLAR x y z")==0)
            {
                alan=3;
            }
        }
        if(i==3)
        {
            sscanf(tut[i],"%s%s",&oyle,&sayi);
            flag=atoi(sayi);
        }
    }
    i=0;
    while(i<flag)
    {
        if(alan==3)
            fread(nokta,sizeof(nokta),1,dosya);
        else if(alan==6)
            fread(noktar,sizeof(noktar),1,dosya);
        i++;
    }
    if(alan==3)
    {
        int k;
        struct noktalar enbuyuk;
        struct noktalar enkucuk;
        float ekle,dizi[3];
        enbuyuk.x=nokta[0].x;
        enbuyuk.y=nokta[0].y;
        enbuyuk.z=nokta[0].z;
        enkucuk.x=nokta[0].x;
        enkucuk.y=nokta[0].y;
        enkucuk.z=nokta[0].z;
        for(k=1; k<flag; k++)
        {
            if(nokta[k].x>enbuyuk.x)
                enbuyuk.x=nokta[k].x;

            if(nokta[k].y>enbuyuk.y)
                enbuyuk.y=nokta[k].y;

            if(nokta[k].z>enbuyuk.z)
                enbuyuk.z=nokta[k].z;

            if(nokta[k].x<enkucuk.x)
                enkucuk.x=nokta[k].x;

            if(nokta[k].y<enkucuk.y)
                enkucuk.y=nokta[k].y;

            if(nokta[k].z<enkucuk.z)
                enbuyuk.z=nokta[k].z;
        }
        dizi[0]=enbuyuk.x-enkucuk.x;
        dizi[1]=enbuyuk.y-enkucuk.y;
        dizi[2]=enbuyuk.z-enkucuk.z;
        ekle=dizi[0];
        for(k=0; k<3; k++)
        {
            if(dizi[k]>ekle)
                ekle=dizi[k];
        }
        islem[0].x =enbuyuk.x;
        islem[0].y =enbuyuk.y;
        islem[0].z=enbuyuk.z;
        printf("1. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z;
        printf("2. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z-ekle;
        printf("3. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z-ekle;
        printf("4. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z;
        printf("5. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z-ekle;
        printf("6. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z-ekle;
        printf("7. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z;
        printf("8. kose x: %f y: %f z: %f \n\n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
    }
    if(alan==6)
    {
        int k;
        struct noktalar enbuyuk;
        struct noktalar enkucuk;
        float ekle,dizi[3];
        enbuyuk.x=nokta[0].x;
        enbuyuk.y=nokta[0].y;
        enbuyuk.z=nokta[0].z;
        enkucuk.x=nokta[0].x;
        enkucuk.y=nokta[0].y;
        enkucuk.z=nokta[0].z;
        for(k=1; k<flag; k++)
        {
            if(nokta[k].x>enbuyuk.x)
                enbuyuk.x=nokta[k].x;

            if(nokta[k].y>enbuyuk.y)
                enbuyuk.y=nokta[k].y;

            if(nokta[k].z>enbuyuk.z)
                enbuyuk.z=nokta[k].z;

            if(nokta[k].x<enkucuk.x)
                enkucuk.x=nokta[k].x;

            if(nokta[k].y<enkucuk.y)
                enkucuk.y=nokta[k].y;

            if(nokta[k].z<enkucuk.z)
                enbuyuk.z=nokta[k].z;
        }
        dizi[0]=enbuyuk.x-enkucuk.x;
        dizi[1]=enbuyuk.y-enkucuk.y;
        dizi[2]=enbuyuk.z-enkucuk.z;
        ekle=dizi[0];
        for(k=0; k<3; k++)
        {
            if(dizi[k]>ekle)
                ekle=dizi[k];
        }
        islem[0].x =enbuyuk.x;
        islem[0].y =enbuyuk.y;
        islem[0].z=enbuyuk.z;
        printf("1. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z;
        printf("2. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z-ekle;
        printf("3. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z-ekle;
        printf("4. kose x: %f y: %f z: %f \n",enbuyuk.x,enbuyuk.y-ekle,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z;
        printf("5. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y;
        islem[0].z=enbuyuk.z-ekle;
        printf("6. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z-ekle;
        printf("7. kose x: %f y: %f z: %f \n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z-ekle);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
        islem[0].x=enbuyuk.x-ekle;
        islem[0].y=enbuyuk.y-ekle;
        islem[0].z=enbuyuk.z;
        printf("8. kose x: %f y: %f z: %f \n\n",enbuyuk.x-ekle,enbuyuk.y-ekle,enbuyuk.z);
        fwrite(&islem,sizeof(struct noktalar),1,dosya1);
    }
}
void dosyaoku(int secim,char tut[][100],int *sayac,char binarytut[][100],int *sayacb,float *xk,float *yk,float *zk,float *yr)
{
    klasor=opendir(".");
    char g[200],a[100];
    float x=*xk,y=*yk,z=*zk,t=*yr;
    int i=0,sonuc=1,uzunluk,j=0,sonucb=1;
    while( (giris=readdir(klasor)) )
    {
        if(strstr(giris->d_name,".nkt"))
        {
            sprintf(g,"%s",giris->d_name);
            FILE *dosya=fopen(g,"r");
            sprintf(a,"outputs\\output %s",giris->d_name);
            FILE *dosya1=fopen(a,"a");
            if(secim==1)
            {
                printf("\n%s dosyasi:\n",giris->d_name);
                sonuc=kontrol(dosya,dosya1);
                if(sonuc!=0 && sonuc!=2)
                {
                    uzunluk=strlen(g);
                    strcpy(tut[*sayac],g);
                    tut[*sayac][uzunluk]='\0';
                    *sayac+=1;
                }
                if(sonuc==2)
                {
                    FILE *dosya=fopen(g,"rb");
                    sonucb=kontrolb(dosya,dosya1);
                    if(sonucb!=0)
                    {
                        uzunluk=strlen(g);
                        strcpy(binarytut[*sayacb],g);
                        binarytut[*sayacb][uzunluk]='\0';
                        *sayacb+=1;
                    }
                }
                sonuc=1;
                    fclose(dosya);
                    fclose(dosya1);
            }
            if(secim==2)
            {
                if(strcmp(tut[i],g)==0)
                {
                    FILE *dosya=fopen(g,"r");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"a");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    yakinuzak(dosya,dosya1);
                    i++;
                    fclose(dosya);
                    fclose(dosya1);
                }
                if(strcmp(binarytut[j],g)==0)
                {
                    FILE *dosya=fopen(g,"rb");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"ab");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    yakinuzakb(dosya,dosya1);
                    j++;
                    fclose(dosya);
                    fclose(dosya1);
                }
            }
            if(secim==3)
            {

                if(strcmp(tut[i],g)==0)
                {
                    FILE *dosya=fopen(g,"r");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"a");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    kup(dosya,dosya1);
                    i++;
                    fclose(dosya);
                    fclose(dosya1);
                }
                if(strcmp(binarytut[j],g)==0)
                {
                    FILE *dosya=fopen(g,"rb");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"ab");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    kupb(dosya,dosya1);
                    j++;
                    fclose(dosya);
                    fclose(dosya1);
                }
            }
            if(secim==4)
            {
                if(strcmp(tut[i],g)==0)
                {
                    FILE *dosya=fopen(g,"r");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"a");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    kure(dosya,dosya1,&x,&y,&z,&t);
                    i++;
                    fclose(dosya);
                    fclose(dosya1);
                }
                if(strcmp(binarytut[j],g)==0)
                {
                    FILE *dosya=fopen(g,"rb");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"ab");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    kureb(dosya,dosya1,&x,&y,&z,&t);
                    j++;
                    fclose(dosya);
                    fclose(dosya1);
                }

            }
            if(secim==5)
            {
                if(strcmp(tut[i],g)==0)
                {
                    FILE *dosya=fopen(g,"r");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"a");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    noktaortalama(dosya,dosya1);
                    i++;
                    fclose(dosya);
                    fclose(dosya1);
                }
                if(strcmp(binarytut[j],g)==0)
                {
                    FILE *dosya=fopen(g,"rb");
                    sprintf(a,"outputs\\output %s",giris->d_name);
                    FILE *dosya1=fopen(a,"ab");
                    printf("\n%s dosyasi:\n",giris->d_name);
                    noktaortalamab(dosya,dosya1);
                    j++;
                    fclose(dosya);
                    fclose(dosya1);
                }
            }
        }
    }
    closedir(klasor);
}
int main()
{
    int dosyasayisi=0,secim,sayac=0,sayacb=0;
    char g[100],tut[100][100],binarytut[100][100];
    float xk,yk,zk,yr;
    mkdir("outputs");
    klasor=opendir(".");
    while( (giris=readdir(klasor)))
    {
        dosyasayisi++;//2 fazla bastiriyor
        if(dosyasayisi>2)
        {
            if(strstr(giris->d_name,".nkt"))
            {
                sprintf(g,"outputs\\output %s",giris->d_name);
                FILE *dosya=fopen(g,"w");
                fclose(dosya);
            }
        }
    }
    klasor=closedir(klasor);
    printf("MENU:\n1-Dosya Kontrolu\n2-Birbirine En Yakin ve En Uzak Noktalar\n3-Tum Noktalari Icine Alacak Bir Kupun Kose Nokta Bilgileri\n");
    printf("4-Merkezi Koordinatlari ve Yaricapi Kullanicidan Alinan Kurenin Icindeki Noktalar\n5-Her Bir Noktanin Birbirine Olan Uzakliklarinin Ortalamasi\n");
    while(1)
    {
        printf("Seciminizi girin:");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            dosyaoku(secim,tut,&sayac,binarytut,&sayacb,&xk,&yk,&zk,&yr);
            break;
        case 2:
            dosyaoku(secim,tut,&sayac,binarytut,&sayacb,&xk,&yk,&zk,&yr);
            break;
        case 3:
            dosyaoku(secim,tut,&sayac,binarytut,&sayacb,&xk,&yk,&zk,&yr);
            break;
        case 4:
            printf("Kurenizin merkez koordinatlari ve yaricapini giriniz:");
            scanf("%f%f%f%f",&xk,&yk,&zk,&yr);
            dosyaoku(secim,tut,&sayac,binarytut,&sayacb,&xk,&yk,&zk,&yr);
            break;
        case 5:
            dosyaoku(secim,tut,&sayac,binarytut,&sayacb,&xk,&yk,&zk,&yr);
            exit(1);
        default:
            printf("Yanlis Tercih yaptiniz..\n");
        }
    }
    return 0;
}
