#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "stdio.h"
#include <time.h>
#include "exec.h"
#define TRUE 1

//STRUCTS
typedef struct{
    char path[200];
    char id[10];
    char name[100];
    struct registro *siguiente;
    struct registro *anterior;
}registro;
typedef struct{
    registro *primero;
    registro *ultimo;
    int tam;
}tabla;
typedef struct{
    int numero;
    struct nodolista *siguiente;
    struct nodolista *anterior;
}nodolista;
typedef struct{
   nodolista *primero;
   nodolista *ultimo;
    int tam;
}lista;
typedef struct{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
    struct nodolistaebr *siguiente;
    struct nodolistaebr *anterior;
}nodolistaebr;
typedef struct{
    nodolistaebr *primero;
    nodolistaebr *ultimo;
    int tam;
}listaebr;
typedef struct{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    int  part_status;
    char part_type[100];
    char part_fit[100];
    int  part_start;
    int  part_size;
    char part_name[25];
    int  existeebr;
    int  EsMbr;
    struct reportedisk *siguiente;
    struct reportedisk *anterior;
}reportedisk;
typedef struct{
    reportedisk *primero;
    reportedisk *ultimo;
    int tam;
}listareportedisk;
typedef struct{
    int  part_status;
    char part_type[100];
    char part_fit[100];
    int  part_start;
    int  part_size;
    char part_name[25];
}partition;
typedef struct{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    partition mbr_partition1;
    partition mbr_partition2;
    partition mbr_partition3;
    partition mbr_partition4;
}mbr;
typedef struct{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
}ebr;

//VARIABLES GLOBALES
lista* listanumeros;
tabla *re;
listareportedisk * reportedisk1;
listaebr *listalogicas;
int logsumasize=0;
int lognombreexiste=0;
int globalcu=0;
char* comprobarcadena[200];
int numcirr;
int EsExec=0;

int main(){

//INICIAR TODAS LAS ESTRUCTURAS
    reportedisk1=(listareportedisk*)malloc(sizeof(listareportedisk));
    reportedisk1->primero=(listareportedisk*)malloc(sizeof(listareportedisk));
    reportedisk1->ultimo=(listareportedisk*)malloc(sizeof(listareportedisk));
    reportedisk1->primero=NULL;
    reportedisk1->ultimo=NULL;
    reportedisk1->tam=0;

    listalogicas=(listaebr*)malloc(sizeof(listaebr));
    listalogicas->primero=(listaebr*)malloc(sizeof(listaebr));
    listalogicas->ultimo=(listaebr*)malloc(sizeof(listaebr));
    listalogicas->primero=NULL;
    listalogicas->ultimo=NULL;
    listalogicas->tam=0;

    re = (tabla *)malloc(sizeof(tabla));
    re->primero = (registro *)malloc(sizeof(registro));
    re->ultimo = (registro *)malloc(sizeof(registro));
    re->primero = NULL;
    re->ultimo = NULL;
    re->tam=0;

    listanumeros =(lista*)malloc(sizeof(lista));
    listanumeros->primero =(lista*)malloc(sizeof(lista));
    listanumeros->ultimo =(lista*)malloc(sizeof(lista));
    listanumeros->primero=NULL;
    listanumeros->ultimo=NULL;
    listanumeros->tam=0;

//FINN INICAR LAS ESTRUCTURAS
    char cadena[300];


    printf("Ingrese Orden\n");

    while(TRUE==1){

        fgets(cadena,300,stdin);

        char *quitarsalto=strtok(cadena,"\n\t");
        strcpy(cadena,quitarsalto);
        leerComandos(cadena);


    }

  return 0;
}

//METODOS FASE 1
int leerComandos(char *cadena[300]){
   char CadenaSalto[200];
    char Comando[300];
    strcpy(CadenaSalto,"");

if(strstr(cadena,"#")){
            return -1;
        }

        int HaySalto =0;

        while(strstr(cadena,"\\")){
            char *token1 =strtok(cadena,"\\");
            strcat(CadenaSalto,token1);
            strcat(CadenaSalto," ");
            fgets(cadena,300,stdin);
            HaySalto=1;
        }

        if(HaySalto==1){
            strcpy(Comando,CadenaSalto);
            strcat(Comando," ");
            strcat(Comando,cadena);
        }else{
            strcpy(Comando,cadena);
        }

        strcpy(cadena,"");
        strcpy(CadenaSalto,"");

       //COMANDO YA TIENE LA CADENA COMPLETA;

      // printf("\n-----------------------------CADENA COMPLETA:   %s\n",Comando);

       char *Minuscula;
       for(Minuscula = Comando; *Minuscula; Minuscula++){
            *Minuscula = tolower((unsigned char)*Minuscula);
            }


        // LA CADENA COMANDO YA ESTA TODA EN MINUSCULAS
        strcpy(comprobarcadena,Comando);
        char *token =strtok(Comando," ");

        //TOKEN CONTIENE LA PRIMERA ORDEN

        //ACONTINUACION SE LLAMA A EL METODO SEGUN LA ORDEN

        if(strcmp(token,"mkdisk")==0){
            mkdisk(token);
           /// printf("-------PASO-----\n");
        }
        else if(strcmp(token,"rmdisk")==0){
            rmdisk(token);
        }
        else if(strcmp(token,"fdisk")==0){
       // printf("COMANDOS LEIDOS!!!!!! ANTES FDISK--\n");

            fdisk(token);
       // printf("COMANDOS LEIDOS!!!!!! DESPUES FDISK--\n");

        }
        else if(strcmp(token,"mount")==0){

            mount(token);

        }
        else if(strcmp(token,"umount")==0){
            umount(token);
        }
        else if(strcmp(token,"rep")==0){
            rep(token);
        }
        else if(strcmp(token,"exec")==0){

            exec(token);

        } else if(strcmp(cadena,"\n")==0){ }
        return 0;
}
int exec (char *token){
if(strstr(comprobarcadena,"\"/") && strstr(comprobarcadena,".sh\"")){
    }else{printf("\nError al directorio compruebe la extension .sh\n"); return -1;}

    char path[150]="";
    int veces=0;

    while(token!=NULL){
       // printf(" ejecucion1-------------------------------%s \n",token);

        token=strtok(NULL,":\"\n");
      //  printf(" ejecucion2-------------------------------%s \n",token);
        if(token==NULL){
            break;
        }
        strcpy(path,token);
        veces++;

    }

     FILE *file1;

    char *c1;
    char cadena[200]="";


    file1=fopen(path,"r");

    if(file1 ==NULL){
        printf("\nArchivo de Script inexistente\n");
        return -1;
    }

    while(c1=fgets(cadena,200,file1)){

    /***********************************************************************************************************/
        int  HaySalto=0;
        char CadenaSalto[200];
        char Comando1[200];

        strcpy(CadenaSalto,"");

        while(strstr(cadena,"\\")){
            char *token1 =strtok(cadena,"\\");
            strcat(CadenaSalto,token1);
            strcat(CadenaSalto," ");
            fgets(cadena,200,file1);
            HaySalto=1;
        }

        if(HaySalto==1){
            strcat(CadenaSalto,cadena);
            strcat(cadena,CadenaSalto);
            //strcat(Comando,cadena);
        }

        strcpy(CadenaSalto,"");

    /*********************************************************************************************************************************/



    if(strstr(cadena,"-")||strstr(cadena,"m")||strstr(cadena,"i")||strstr(cadena,"u")||strstr(cadena,"s")||strstr(cadena,"+")||strstr(cadena,"f")){}
    else{break;}
       printf("%s\n",cadena);
       char *quitarsalto=strtok(cadena,"\n\t");

        strcpy(cadena,quitarsalto);

        EsExec==1;
       // printf("COMANDOS LEIDOS!!!!!!--%s\n",cadena);
       leerComandos(cadena);

        EsExec=0;
    }
       fclose(file1);

return 0;
}
int mkdisk(char*token){
if(strstr(comprobarcadena,"\"/") || strstr(comprobarcadena,"/\"")){
    }else{printf("\nError en el comando\n"); return -1;}

char size[20]="-size";
char unit[20]="+unit";
char path[20]="-path";
char name[20]="-name";

//COMPROBANDO QUE TIENE LOS PARAMETROS OBLIGATORIOS
//printf("LA CADENA ES %s\n",comprobarcadena);
if(strstr(comprobarcadena,size) &&strstr(comprobarcadena,name)&& strstr(comprobarcadena,path) && strstr(comprobarcadena,".dsk\"")&& strstr(comprobarcadena,"/\"")&& strstr(comprobarcadena,"\"/home")){
//printf("PROBANDO UNO\n");
}else{
printf("\nComando NO cuenta con parametros minimos o mal escritos\n");
return -1;
}


char comillas[2]="\"";
int control=0;
int tamanioDeDisco;
char unitletra[5]="m";
char Nombre[200];
char dpth[200];
char dpth2[200];
char dpth3[200];
while(token !=NULL){

    token = strtok(NULL," ::");
    if(token==NULL) break;

    char *estaSize;
    char *estaUnit;
    char *estaPath;
    char *estaName;

    estaSize = strstr(token,size);
    estaUnit = strstr(token,unit);
    estaPath = strstr(token,path);
    estaName = strstr(token,name);

    if(estaSize) control=1;
    if(estaUnit) control=2;
    if(estaPath) control=3;
    if(estaName) control=4;

    switch(control){
    case 1:
        token = strtok(NULL," :");
        tamanioDeDisco=atoi(token);
        if(tamanioDeDisco <=9){
            printf("\nTamaño De Disco Invalido\n");
         return -1;
        }
        break;
     case 2:
        token= strtok(NULL," ::");
        strcpy(unitletra,token);
        if((strcmp(unitletra,"m") == 0) || (strcmp(unitletra,"k") == 0)){
        }else{
            printf("\nUnidad Invalida.\n");
            return -1;
        }
        break;
     case 3:
       // printf("token1  ------%s\n",token);
        //token=strtok(NULL,":\"\n");
       // token = strtok(NULL," ");
        token=strtok(NULL,":\"\n");
        if(strstr(token,comillas)){
            printf("token3  ------%s\n",token);
            strcpy(dpth,token);
            strcpy(dpth2,dpth);
            strcpy(dpth3,dpth);
        }else{
            //token = strtok(NULL,":");
            strcpy(dpth,token);
            strcpy(dpth2,token);
            strcpy(dpth3,token);
        }
      //  printf("dpth %s\n",dpth);
       // printf("dpth2 %s\n",dpth2);
       // printf("dpth3 %s\n",dpth3);

        break;


    case 4:
        //token = strtok(NULL," ::");
        token=strtok(NULL,":\"\n");
        if(strstr(token,comillas)){
          //  token=strtok(NULL,"\"");
            strcpy(Nombre,token);

        }else{
            strcpy(Nombre,token);
        }

        if(strstr(Nombre,".dsk")){
        printf("\nNombre verificado\n");
        }else{
        printf("\nExtension de nombre invalida\n");
       return -1;
        }


        break;

      default:
        printf("\nAccion invalida o Inexistente.\n");

        return -1;

        break;
    }
}

        //VERIFICANDO PATH QUE SEA CORRECTO
        if((tamanioDeDisco <=9 && strcmp(unitletra,"m")==0)||(tamanioDeDisco <10240 && strcmp(unitletra,"k")==0)){
            printf("\nEl tamaño de disco debe ser mayor a 9MB o mayor a 10240KB\n");
         return -1;
        }
    //SE CREA EL PATH

    strcat(dpth,Nombre);
    strcat(dpth2,Nombre);
    strcat(dpth3,Nombre);
    int numPalabras =1;
    char *tem;
    tem =strtok(dpth,"/");

    while(tem!=NULL){
        tem =strtok(NULL,"/");
        if(tem==NULL) break;
        numPalabras++;
    }

    char pathReal[200]="/";
    char*aux11;
    aux11= strtok(dpth2,"/");
    strcat(pathReal,aux11);
    strcat(pathReal,"/");
    while(numPalabras > 2)
    {
        aux11 = strtok(NULL,"/");
        strcat(pathReal,aux11);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    aux11 = strtok(NULL,"/");

    mbr *mbr1 =(mbr*)malloc(sizeof(mbr));
    FILE *archivo = fopen(dpth3,"wb");

    //obteniendo fecha del sistema
    timer_t tiempo = time(0);
    struct tm *tlocal=localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);

    strcpy(mbr1->mbr_fecha_creacion,output);

    int random = rand();
    mbr1->mbr_disk_signature=random;


    mbr1->mbr_partition1.part_size =0;
    mbr1->mbr_partition2.part_size =0;
    mbr1->mbr_partition3.part_size =0;
    mbr1->mbr_partition4.part_size =0;
    mbr1->mbr_partition1.part_start=0;
    mbr1->mbr_partition2.part_start=0;
    mbr1->mbr_partition3.part_start=0;
    mbr1->mbr_partition4.part_start=0;

    strcpy(mbr1->mbr_partition1.part_type,"x");
    strcpy(mbr1->mbr_partition2.part_type,"x");
    strcpy(mbr1->mbr_partition3.part_type,"x");
    strcpy(mbr1->mbr_partition4.part_type,"x");



    if(strcmp(unitletra, "k")==0){
       mbr1->mbr_tamanio= tamanioDeDisco*1024;
       //fseek(archivo,0,SEEK_SET);
       fwrite(mbr1,sizeof(mbr),1,archivo);
       int h =0;
       for(h; h<500*tamanioDeDisco;h++){
           fputs("\\0",archivo);
       }
    }else if(strcmp(unitletra,"m") == 0){
           mbr1->mbr_tamanio=tamanioDeDisco*1024*1024;
           //fseek(archivo,0,SEEK_SET);
           fwrite(mbr1,sizeof(mbr),1,archivo);
           int i=0;
           for(i;i< 2*(500*tamanioDeDisco*500);i++){
               fputs("\\0",archivo);
           }

}
    printf("\nDisco creado Con exito\n");
fclose(archivo);
/**************************/

mbr *mbrLeido=(mbr*)malloc(sizeof(mbr));
FILE *archivo1 =fopen(dpth3,"rb");
fread(mbrLeido,sizeof(mbr),1,archivo1);
int t= sizeof(mbrLeido);
printf("\ntamannio: %d\n", mbrLeido->mbr_tamanio);

fclose(archivo1);
return 1;
/**************************/


}
int rmdisk(char *token){
if(strstr(comprobarcadena,"\"/") && strstr(comprobarcadena,".dsk\"")){
    }else{printf("\nError en el comando\n"); return -1;}
    token = strtok(NULL," :");

char* path[200];

if(strstr(token,"-path")){

}
else{
    printf("\nComando de path invalido\n");
    return -1;
}

//token =strtok(NULL,":");
token=strtok(NULL,":\"\n");
strcpy(path,token);

if(strstr(token,"\"")){

 // token=strtok(token,"\"");

  strcpy(path,token);

}


FILE* ArchivoBorrar =fopen(path,"r");
printf(path);
if(ArchivoBorrar){
    printf("\nSeguro que desea eliminar disco (escriba si o no):\n");
    char *confirmacion[10];
    fgets(confirmacion,10,stdin);
    char *quitarsalto=strtok(confirmacion,"\n");
    strcpy(confirmacion,quitarsalto);

    if(strcmp(confirmacion,"si")==0){
        remove(path);
        printf("\nDisco eliminado\n");

    }else if(strcmp(confirmacion,"no")==0){
       printf("\nDisco No eliminado\n");
       fclose(ArchivoBorrar);
    }else{
        printf("\nRespuesta invalida, no se ejecuto ninguna accion.\n");
        fclose(ArchivoBorrar);
    }

}else{
    printf("\nArchivo a Borrar No Existe\n");
}

return 1;

}
int fdisk(char *token){
//printf("ENTRO 1");
if(strstr(comprobarcadena,"\"/") && strstr(comprobarcadena,".dsk\"")){
//printf("ENTRO 2");
    }else{printf("\nError en el comando\n"); return -1;}
    int    op = 0;
    int    size1=0;
    char*  unit1[5];
    char*  path1[200];
    char*  type1[5];
    char*  fit1[5];
    char*  delete1[20];
    char*  name1[50];
    int    add1=0;
    char*  add11[20];
    int  Menos=0;
    int delete11=0;

    //aca se mira si hay comandos comprobarcadenas
    if(strstr(comprobarcadena,"add") && strstr(comprobarcadena,"delete") || strstr(comprobarcadena,"add") && strstr(comprobarcadena,"size") || strstr(comprobarcadena,"size") && strstr(comprobarcadena,"delete")){
   printf("\nError comandos comprobarcadenas\n");
   return -1;
   }
   //SE VERIFICA QUE ESTE TODA LA INFORMACION DE SIZE
    if(strstr(comprobarcadena,"-size")){

       if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){
   //printf("ENTRO 3");
       }else{
           printf("\nFalta Informacion\n");
           return -1;
       }
   }
   //SE VERIFICA QUE ESTE TODA LA INFORMACION DEL DELETE
    if(strstr(comprobarcadena,"+delete")){


       if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){

       }else{
           printf("\nFalta Informacion\n");
       return -1;
       }
   }
    //SE VERIFICA QUE ESTE TODA LA INFORMACIOND EL ADD
    if(strstr(comprobarcadena,"+add")){
      if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name")){

       }else{
           printf("\nFalta Informacion\n");
       return -1;
       }

   }
    //SE COLOCAN LOS VALORES POR DEFECTO

    strcpy(fit1,"wf");
    strcpy(unit1,"k");
    strcpy(type1,"p");

     //   printf("\nponiendo token %s\n",token);
    //SE ANALIZA LA CADENA A EJECUTAR
     while(token !=NULL){
        token=strtok(NULL," :");
        if(token==NULL) break;
        if(strstr(token,"-size"))    op=1;
        if(strstr(token,"+unit"))    op=2;
        if(strstr(token,"-path"))    op=3;
        if(strstr(token,"+type"))    op=4;
        if(strstr(token,"+fit"))     op=5;
        if(strstr(token,"+delete"))  op=6;
        if(strstr(token,"-name"))    op=7;
        if(strstr(token,"+add"))     op=8;
     //   printf("\nponiendo token Q%sQ ---- %d\n",token, op);
     switch(op){
      case 1:
        token=strtok(NULL," :");
        size1=atoi(token);
        if(token==NULL){
        printf("\nComando invalido o mal escrito\n");
        return -1;
        }else if(size1 <=0){
            printf("\nTamaño de particion invalido\n");
            return -1;
        }
          break;
      case 2:
        token=strtok(NULL," :");
        strcpy(unit1,token);
        if(token==NULL){
        printf("\nComando invalido o mal escrito\n");
        return -1;
        }else if(strcmp(unit1,"m")!=0 && strcmp(unit1,"k")!=0 && strcmp(unit1,"b")!=0){

            printf("\nUnidad  invalida.\n");
            return -1;
        }
        break;
      case 3:
         token=strtok(NULL,":\"\n");
          //token = strtok(NULL,": ");
      char *tok;
      if(strstr(token,"\"")){
       // tok=strtok(token,"\"");
        strcpy(path1,tok);
      }else{
          strcpy(path1,token);
      }
      FILE* comprobar =fopen(path1,"r");
      if(comprobar){
      fclose(comprobar);
      }else{
      printf("\nArchivo Inexistente\n");
      return -1;
      }

          break;
      case 4:
          token=strtok(NULL," :");
          strcpy(type1,token);
          if(strcmp(type1,"p")!=0 && strcmp(type1,"e")!=0 && strcmp(type1,"l")!=0){
              printf("\nTipo de particion invalida\n");
              return -1;
          }
          break;
      case 5:
          token =strtok(NULL," :");
          strcpy(fit1,token);
          if(strcmp(fit1,"bf")!=0 && strcmp(fit1,"ff")!=0 && strcmp(fit1,"wf")!=0){
              printf("\nAjuste de particion invalido\n");
              return -1;
          }
          break;
      case 6:
          token =strtok(NULL," :");
          strcpy(delete1,token);
          delete11=1;
          if(strcmp(delete1,"full")!=0 && strcmp(delete1,"fast")!=0){
              printf("\nTipo de eliminacion invalido\n");
              return -1;
          }
          break;

      case 7:
      token=strtok(NULL,":\"\n");
          //token =strtok(NULL," :");
          strcpy(name1,token);
          if(name1==NULL){
              printf("\nNombre invalido\n");
              return -1;
          }
          break;
      case 8:
          token =strtok(NULL," :");
          strcpy(add11,token);
          if(add11!=NULL){
          if(strstr(add11,"-")){
           Menos = 1;
           char* tok1;
           tok1 = strtok(add11,"- :");
           strcpy(add11,tok1);
           add1 =atoi(add11);
          }else{
              add1=atoi(add11);
          }
          }else{
              printf("\nvalor de add incorrecto o inexistente.\n");
          return -1;
          }
          break;
      default:
          printf("\ncomandos invalidos\n");
          return -1;
          break;

        }

    }
 //   printf("ENTRO 1 slio while");

    mbr* mbraux=(mbr*)malloc(sizeof(mbr));
    FILE* file = fopen(path1,"r+b");
    fseek(file,0,SEEK_SET);
    fread(mbraux,sizeof(mbr),1,file);
    fclose(file);

    if(strcmp(unit1,"b")==0){
        size1= size1;
        add1 = add1;
    }else if(strcmp(unit1,"k")==0){
        size1=size1*1024;
        add1 =add1 *1024;
    }else if(strcmp(unit1, "m")==0){
        size1=size1*1024*1024;
        add1 =add1 *1024*1024;
    }
    //comprobando que hay suficiente espacio en el disco
    int EspacioLibreEnDisco;
       EspacioLibreEnDisco=mbraux->mbr_tamanio-mbraux->mbr_partition1.part_size-mbraux->mbr_partition2.part_size-mbraux->mbr_partition3.part_size-mbraux->mbr_partition4.part_size;
    int cabeParticion;

    cabeParticion=EspacioLibreEnDisco-size1;
    //SI LA PARTICION A CREAR CABE EN EL DISCO ENTONCES CabeParticion SERA 1 en otro caso sera -1
    if(cabeParticion>0){
    cabeParticion=1;
    }else{
    cabeParticion=-1;
    }

    //COMPROVANO RESTRICCIONES POR TEORIA DE PARTICIONES

    mbr *mbr01=(mbr*)malloc(sizeof(mbr));
    FILE *partc =fopen(path1,"r+b");

    fseek(partc,0,SEEK_SET);
    fread(mbr01,sizeof(mbr),1,partc);
    fclose(partc);

   if(strstr(comprobarcadena,"type")){


       if(strcmp(type1,"e")==0){
            if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
            if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){printf("\nYa existe una particion Extendida\n"); return -1;}
        }
        if(strcmp(type1,"l")==0){
        if(strcmp(mbr01->mbr_partition1.part_type,"e")!=0 && strcmp(mbr01->mbr_partition2.part_type,"e")!=0 && strcmp(mbr01->mbr_partition3.part_type,"e")!=0 && strcmp(mbr01->mbr_partition4.part_type,"e")!=0)
        {
            printf("\nNO existe una particion Extendida\n");
               return -1;
        }
        }
        if(strcmp(type1,"l")!=0 && mbr01->mbr_partition1.part_size>0 && mbr01->mbr_partition2.part_size>0 && mbr01->mbr_partition3.part_size>0 && mbr01->mbr_partition4.part_size>0){
           printf("\nNo hay espacio para otra particion\n");
           return -1;
        }
    }


    //SI SE CREA UNA NUEVA PARTICION
    if(size1>0){
   // printf("ENTRO en size>0");
    //VEROFOCANDO QUE EL NOMBRE NO EXISTA AUN
    if(strcmp(mbraux->mbr_partition1.part_name,name1)==0 || strcmp(mbraux->mbr_partition2.part_name,name1)==0 || strcmp(mbraux->mbr_partition3.part_name,name1)==0 || strcmp(mbraux->mbr_partition4.part_name,name1)==0){
          printf("/nnombre de particion ya existe/n");
          return -1;
       }
       if(mbraux->mbr_partition1.part_size>0 && mbraux->mbr_partition2.part_size>0 && mbraux->mbr_partition3.part_size>0 && mbraux->mbr_partition4.part_size>0){
       printf("/nYa Existen cuatro particiones, ya no cabe otra/n");

       }


      if(strcmp("l",type1)!=0){
        //SI PARTICION UNO ESTA VACIA
      if(mbr01->mbr_partition1.part_size==0){

        int inicio=0;
        inicio=IniciarParticion(mbraux->mbr_partition2.part_start,mbraux->mbr_partition2.part_size,mbraux->mbr_partition3.part_start,mbraux->mbr_partition3.part_size,mbraux->mbr_partition4.part_start,mbraux->mbr_partition4.part_size,size1,mbraux->mbr_tamanio);

        if(inicio<0){
        printf("\nParticion demasiado grande\n");
        return -1;
        }


    strcpy(mbr01->mbr_partition1.part_fit,fit1);
    strcpy(mbr01->mbr_partition1.part_name,name1);
    strcpy(mbr01->mbr_partition1.part_type,type1);
    mbr01->mbr_partition1.part_size    =size1;
    mbr01->mbr_partition1.part_start   =inicio;
    mbr01->mbr_partition1.part_status  =1;


    FILE *partc11 =fopen(path1,"rb+");
    fseek(partc11,0,SEEK_SET);
    fwrite(mbr01,sizeof(mbr),1,partc11);
    fclose(partc11);

    if(strcmp(type1,"e")==0){
        ebr *ebr1 =(ebr*)malloc(sizeof(ebr));
        ebr1->part_status=1;
        FILE* amigo=fopen(path1,"rb+");
        fseek(amigo,0,SEEK_SET);
        mbr* auxiliar=(mbr*)malloc(sizeof(mbr));
        fread(auxiliar,sizeof(mbr),1,amigo);
        fseek(amigo,inicio,SEEK_CUR);
        strcpy(ebr1->part_fit,"");
        ebr1->part_status=0;
        ebr1->part_start=-1;
        ebr1->part_size=0;
        ebr1->part_next=-1;
        strcpy(ebr1->part_name,"");
        fwrite(ebr1,sizeof(ebr),1,amigo);

        fclose(amigo);

    }
    printf("\nParticion Creada Con exito\n");

   }


         //SI PARTICION DOS ESTA VACIA
        else   if(mbr01->mbr_partition2.part_size==0){

        int inicio=0;
        inicio=IniciarParticion(mbraux->mbr_partition1.part_start,mbraux->mbr_partition1.part_size,mbraux->mbr_partition3.part_start,mbraux->mbr_partition3.part_size,mbraux->mbr_partition4.part_start,mbraux->mbr_partition4.part_size,size1,mbraux->mbr_tamanio);

        if(inicio<0){
        printf("\nParticion demasiado grande\n");
        return -1;
        }

        strcpy(mbr01->mbr_partition2.part_fit,fit1);
        strcpy(mbr01->mbr_partition2.part_name,name1);
        strcpy(mbr01->mbr_partition2.part_type,type1);
        mbr01->mbr_partition2.part_size    =size1;
        mbr01->mbr_partition2.part_start   =inicio;
        mbr01->mbr_partition2.part_status  =1;

    FILE *partc11 =fopen(path1,"rb+");
    fseek(partc11,0,SEEK_SET);
    fwrite(mbr01,sizeof(mbr),1,partc11);
    fclose(partc11);

    if(strcmp(type1,"e")==0){
        ebr *ebr1 =(ebr*)malloc(sizeof(ebr));
        ebr1->part_status=1;
        FILE* amigo=fopen(path1,"rb+");
        fseek(amigo,0,SEEK_SET);
        mbr* auxiliar=(mbr*)malloc(sizeof(mbr));
        fread(auxiliar,sizeof(mbr),1,amigo);
        fseek(amigo,inicio,SEEK_CUR);
        strcpy(ebr1->part_fit,"");
        ebr1->part_status=0;
        ebr1->part_start=-1;
        ebr1->part_size=0;
        ebr1->part_next=-1;
        strcpy(ebr1->part_name,"");
        fwrite(ebr1,sizeof(ebr),1,amigo);

        fclose(amigo);

    }
printf("\nParticion Creada Con exito\n");
   }

         //SI PARTICION TRES ESTA VACIA
        else if(mbr01->mbr_partition3.part_size==0){

        int inicio=0;
        inicio=IniciarParticion(mbraux->mbr_partition1.part_start,mbraux->mbr_partition1.part_size,mbraux->mbr_partition2.part_start,mbraux->mbr_partition2.part_size,mbraux->mbr_partition4.part_start,mbraux->mbr_partition4.part_size,size1,mbraux->mbr_tamanio);

        if(inicio<0){
        printf("\nParticion demasiado grande\n");
        return -1;
        }

        strcpy(mbr01->mbr_partition3.part_fit,fit1);
        strcpy(mbr01->mbr_partition3.part_name,name1);
        strcpy(mbr01->mbr_partition3.part_type,type1);
        mbr01->mbr_partition3.part_size    =size1;
        mbr01->mbr_partition3.part_start   =inicio;
        mbr01->mbr_partition3.part_status  =1;

    FILE *partc11 =fopen(path1,"rb+");
    fseek(partc11,0,SEEK_SET);
    fwrite(mbr01,sizeof(mbr),1,partc11);
    fclose(partc11);

    if(strcmp(type1,"e")==0){
        ebr *ebr1 =(ebr*)malloc(sizeof(ebr));
        ebr1->part_status=1;
        FILE* amigo=fopen(path1,"rb+");
        fseek(amigo,0,SEEK_SET);
        mbr* auxiliar=(mbr*)malloc(sizeof(mbr));
        fread(auxiliar,sizeof(mbr),1,amigo);
        fseek(amigo,inicio,SEEK_CUR);
        strcpy(ebr1->part_fit,"");
        ebr1->part_status=0;
        ebr1->part_start=-1;
        ebr1->part_size=0;
        ebr1->part_next=-1;
        strcpy(ebr1->part_name,"");
        fwrite(ebr1,sizeof(ebr),1,amigo);

        fclose(amigo);

    }
    printf("\nParticion Creada Con exito\n");
   }

           //SI PARTICION CUATRO ESTA VACIA
        else if(mbr01->mbr_partition4.part_size==0){
      //   printf("ENTRO particion cuatro");
        int inicio=0;
        inicio=IniciarParticion(mbraux->mbr_partition1.part_start,mbraux->mbr_partition1.part_size,mbraux->mbr_partition3.part_start,mbraux->mbr_partition3.part_size,mbraux->mbr_partition2.part_start,mbraux->mbr_partition2.part_size,size1,mbraux->mbr_tamanio);

        if(inicio<0){
        printf("\nParticion demasiado grande\n");
        return -1;
        }

        strcpy(mbr01->mbr_partition4.part_fit,fit1);
        strcpy(mbr01->mbr_partition4.part_name,name1);
        strcpy(mbr01->mbr_partition4.part_type,type1);
        mbr01->mbr_partition4.part_size    =size1;
        mbr01->mbr_partition4.part_start   =inicio;
        mbr01->mbr_partition4.part_status  =1;

    FILE *partc11 =fopen(path1,"rb+");
    fseek(partc11,0,SEEK_SET);
    fwrite(mbr01,sizeof(mbr),1,partc11);
    fclose(partc11);

    if(strcmp(type1,"e")==0){
        ebr *ebr1 =(ebr*)malloc(sizeof(ebr));
        ebr1->part_status=1;
        FILE* amigo=fopen(path1,"rb+");
        fseek(amigo,0,SEEK_SET);
        mbr* auxiliar=(mbr*)malloc(sizeof(mbr));
        fread(auxiliar,sizeof(mbr),1,amigo);
        fseek(amigo,inicio,SEEK_CUR);
        strcpy(ebr1->part_fit,"");
        ebr1->part_status=0;
        ebr1->part_start=-1;
        ebr1->part_size=0;
        ebr1->part_next=-1;
        strcpy(ebr1->part_name,"");
        fwrite(ebr1,sizeof(ebr),1,amigo);

        fclose(amigo);

    }
    printf("\nParticion Creada Con exito\n");
   }
}
   if(strcmp("l",type1)==0){

/*******************************************************************************************************************************************************************************************************************************/
          if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
              FILE* file = fopen(path1,"rb+");
              mbr* mbraux=(mbr*)malloc(sizeof(mbr));
              fseek(file,0,SEEK_SET);
              fread(mbraux,sizeof(mbr),1,file);
              fclose(file);
             // printf("\ntam en if de logica %d\n",mbraux->mbr_tamanio);

                /* enviarebrs(path1);
                 if(mbr01->mbr_partition1.part_size<logsumasize){
                     vaciarlisebr();
                     logsumasize=0;
                     printf("\nya no hay espacio para una particion tan grande.\n");
                    return -1;
                 }
                 vaciarlisebr();
                 logsumasize=0;*/
              int inicio =mbr01->mbr_partition1.part_start;
                int size =mbr01->mbr_partition1.part_size;

                if(size<size1){
                    printf("\nparticion logica mas grande que la extendida total\n");
                            return -1;
                }
//CA<
int asasdadadasdas;
                FILE *archivo=fopen(path1,"rb+");

                fseek(archivo,0,SEEK_SET);
                mbr *aux2 =(mbr *)malloc(sizeof(mbr));
                ebr *aux3=(ebr *)malloc(sizeof(ebr));
                fread(aux2,sizeof(mbr),1,archivo);
                fseek(archivo,inicio,SEEK_CUR);
                int cur=ftell(archivo);
                fread(aux3,sizeof(ebr),1,archivo);
                ebr *aux4=(ebr *)malloc(sizeof(ebr));
                int o;
                int contador=0;
                int st;
                FILE* file1 = fopen(path1,"r+b");
                mbr* mbraux1=(mbr*)malloc(sizeof(mbr));
                fseek(file1,0,SEEK_SET);
                fread(mbraux1,sizeof(mbr),1,file1);
                fclose(file1);
                //printf("\n\n\ntam en if de logica FINAL! %d\n\n\n",mbraux1->mbr_tamanio);

                int bandera=0;
                if(aux3->part_next==-1 && aux3->part_size>0){
                    aux3->part_next=aux3->part_size+aux3->part_start;

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    fwrite(aux3,sizeof(ebr),1,archivo);

                    fseek(archivo,0,SEEK_SET);

                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    cur=ftell(archivo);
                    fread(aux3,sizeof(ebr),1,archivo);
                    bandera=1;
                }




               // printf("\nsiguiente de primera particion. %d\n",aux3->part_next);
             /*   while(bandera==0){



                  o=aux3->part_size;
                  int lk;
                  fseek(archivo,o,SEEK_CUR);
                   contador++;

                   if(aux3->part_next==-1){

                       aux3->part_next=aux3->part_size+aux3->part_start;

                       fseek(archivo,lk,SEEK_SET);

                       fwrite(aux3,sizeof(ebr),1,archivo);

                       fseek(archivo,-sizeof(ebr),SEEK_CUR);
                       st=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);


                       break;
                   }else{
                       fseek(archivo,0,SEEK_CUR);
                         lk=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);
;
                   }



                }
                bandera=0;

*/
int lk;
                while(bandera==0){
                  o=aux3->part_size;
                   contador++;
                   if(aux3->part_next==-1){
                        aux3->part_next=aux3->part_size+aux3->part_start;
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        fwrite(aux3,sizeof(ebr),1,archivo);
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        st=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                        break;
                   }else{
                        fseek(archivo,o,SEEK_CUR);
                       //fseek(archivo,0,SEEK_CUR);
                        lk=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                   }
                }
                bandera=0;

                if(aux3->part_size>0){
                fseek(archivo,aux3->part_size,SEEK_CUR);
                }else{

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);

                }

                FILE* file11 = fopen(path1,"r+b");
                mbr* mbraux11=(mbr*)malloc(sizeof(mbr));
                fseek(file11,0,SEEK_SET);
                fread(mbraux11,sizeof(mbr),1,file11);
                fclose(file11);
               // printf("\n\n\ntam en if de logica FINAL22! %d\n\n\n",mbraux11->mbr_tamanio);

                strcpy(aux4->part_fit,fit1);
                aux4->part_status=1;
                if(aux3->part_size>0){
                aux4->part_start=aux3->part_next;

               // printf("\ninicio de nueva particion. %d\n",aux4->part_start);
                }else{
                    aux4->part_start=aux2->mbr_partition1.part_start;
                  //  printf("\ninicio de nueva particion. %d",aux4->part_start);

                }
                aux4->part_size=size1;
                aux4->part_next=-1;
                strcpy(aux4->part_name,name1);




                fwrite(aux4,sizeof(ebr),1,archivo);


/****/

                fseek(archivo,st,SEEK_SET);
                globalcu=ftell(archivo);
                ebr *aux44=(ebr *)malloc(sizeof(ebr));
                fread(aux44,sizeof(ebr),1,archivo);





                fclose(archivo);

                FILE* file12 = fopen(path1,"r+b");
                mbr* mbraux13=(mbr*)malloc(sizeof(mbr));
                fseek(file12,0,SEEK_SET);
                fread(mbraux13,sizeof(mbr),1,file12);
                fclose(file12);
                //printf("\n\n\ntam en if de logica FINAL11! %s\n\n\n",mbraux13->mbr_nam);

                printf("\nDatos de nueva particion Logica.\n");
                printf("\nfit: %s\n",aux4->part_fit);
                printf("\nname: %s\n",aux4->part_name);
                printf("\nsiguiente: %d\n",aux4->part_next);
                printf("\ntama;o: %d\n",aux4->part_size);
                printf("\ninicio: %d\n",aux4->part_start);
                printf("\nestatus: %d\n",aux4->part_status);

          }




 /*********************************************************************************************************************************************************************************************************************/
          if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
             /* enviarebrs(path1);
              if(mbr01->mbr_partition2.part_size<logsumasize){
                  vaciarlisebr();
                  logsumasize=0;
                  printf("\nya no hay espacio para una particion tan grande.\n");
                 return -1;
              }
              vaciarlisebr();
              logsumasize=0;*/
              int inicio =mbr01->mbr_partition2.part_start;
                int size =mbr01->mbr_partition2.part_size;

                if(size<size1){
                    printf("\nparticion logica mas grande que la extendida total\n");
                            return -1;
                }

                FILE *archivo=fopen(path1,"rb+");

                fseek(archivo,0,SEEK_SET);
                mbr *aux2 =(mbr *)malloc(sizeof(mbr));
                ebr *aux3=(ebr *)malloc(sizeof(ebr));
                fread(aux2,sizeof(mbr),1,archivo);
                fseek(archivo,inicio,SEEK_CUR);
                int cur=ftell(archivo);
                fread(aux3,sizeof(ebr),1,archivo);
                ebr *aux4=(ebr *)malloc(sizeof(ebr));
                int o;
                int contador=0;
                int st;


                int bandera=0;
                if(aux3->part_next==-1 && aux3->part_size>0){
                    aux3->part_next=aux3->part_size+aux3->part_start;

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    fwrite(aux3,sizeof(ebr),1,archivo);

                    fseek(archivo,0,SEEK_SET);

                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    cur=ftell(archivo);
                    fread(aux3,sizeof(ebr),1,archivo);
                    bandera=1;
                }




              //  printf("\nsiguiente de primera particion. %d\n",aux3->part_next);
                /*while(bandera==0){



                  o=aux3->part_size;
                  int lk;
                  fseek(archivo,o,SEEK_CUR);
                   contador++;

                   if(aux3->part_next==-1){

                       aux3->part_next=aux3->part_size+aux3->part_start;

                       fseek(archivo,lk,SEEK_SET);

                       fwrite(aux3,sizeof(ebr),1,archivo);

                       fseek(archivo,-sizeof(ebr),SEEK_CUR);
                       st=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);


                       break;
                   }else{
                       fseek(archivo,0,SEEK_CUR);
                         lk=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);
;
                   }



                }
                bandera=0;
*/
int lk;
                while(bandera==0){
                  o=aux3->part_size;
                   contador++;
                   if(aux3->part_next==-1){
                        aux3->part_next=aux3->part_size+aux3->part_start;
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        fwrite(aux3,sizeof(ebr),1,archivo);
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        st=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                        break;
                   }else{
                        fseek(archivo,o,SEEK_CUR);
                       //fseek(archivo,0,SEEK_CUR);
                        lk=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                   }
                }
                bandera=0;

                if(aux3->part_size>0){
                fseek(archivo,aux3->part_size,SEEK_CUR);
                }else{

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);

                }

                strcpy(aux4->part_fit,fit1);
                aux4->part_status=1;
                if(aux3->part_size>0){
                aux4->part_start=aux3->part_next;

             //   printf("\ninicio de nueva particion. %d\n",aux4->part_start);
                }else{
                    aux4->part_start=aux2->mbr_partition2.part_start;
                   // printf("\ninicio de nueva particion. %d",aux4->part_start);

                }
                aux4->part_size=size1;
                aux4->part_next=-1;
                strcpy(aux4->part_name,name1);

                fwrite(aux4,sizeof(ebr),1,archivo);


                fseek(archivo,st,SEEK_SET);
                globalcu=ftell(archivo);
                ebr *aux44=(ebr *)malloc(sizeof(ebr));
                fread(aux44,sizeof(ebr),1,archivo);

                fclose(archivo);


                printf("\nDatos de NUeva particion logica creada\n");
                printf("\nfit: %s\n",aux4->part_fit);
                printf("\nname: %s\n",aux4->part_name);
                printf("\nsiguiente: %d\n",aux4->part_next);
                printf("\ntama;o: %d\n",aux4->part_size);
                printf("\ninicio: %d\n",aux4->part_start);
                printf("\nestatus: %d\n",aux4->part_status);

          }

/***************************************************************************************************************************************************************************************************************************************/
          if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){

              int inicio =mbr01->mbr_partition3.part_start;
                int size =mbr01->mbr_partition3.part_size;

                if(size<size1){
                    printf("\nparticion logica mas grande que la extendida total\n");
                            return -1;
                }

                FILE *archivo=fopen(path1,"rb+");

                fseek(archivo,0,SEEK_SET);
                mbr *aux2 =(mbr *)malloc(sizeof(mbr));
                ebr *aux3=(ebr *)malloc(sizeof(ebr));
                fread(aux2,sizeof(mbr),1,archivo);
                fseek(archivo,inicio,SEEK_CUR);
                int cur=ftell(archivo);
                fread(aux3,sizeof(ebr),1,archivo);
                ebr *aux4=(ebr *)malloc(sizeof(ebr));
                int o;
                int contador=0;
                int st;


                int bandera=0;
                if(aux3->part_next==-1 && aux3->part_size>0){



                 mbr* cargambr1=(mbr*)malloc(sizeof(mbr));

        //fseek(assa,0,SEEK_SET);


                    aux3->part_next=aux3->part_size+aux3->part_start;

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    fwrite(aux3,sizeof(ebr),1,archivo);

                    fseek(archivo,0,SEEK_SET);

                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    cur=ftell(archivo);
                    fread(aux3,sizeof(ebr),1,archivo);
                    bandera=1;
                }




                //printf("\nsiguiente de primera particion. %d\n",aux3->part_next);

int lk;
                while(bandera==0){
                  o=aux3->part_size;
                   contador++;
                   if(aux3->part_next==-1){
                        aux3->part_next=aux3->part_size+aux3->part_start;
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        fwrite(aux3,sizeof(ebr),1,archivo);
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        st=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                        break;
                   }else{
                        fseek(archivo,o,SEEK_CUR);
                       //fseek(archivo,0,SEEK_CUR);
                        lk=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                   }
                }
                bandera=0;


                if(aux3->part_size>0){
                fseek(archivo,aux3->part_size,SEEK_CUR);
                }else{

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);

                }

                strcpy(aux4->part_fit,fit1);
                aux4->part_status=1;
                if(aux3->part_size>0){
                aux4->part_start=aux3->part_next;

                printf("\ninicio de nueva particion. %d\n",aux4->part_start);
                }else{
                    aux4->part_start=aux2->mbr_partition3.part_start;
                    printf("\ninicio de nueva particion. %d",aux4->part_start);

                }
                aux4->part_size=size1;
                aux4->part_next=-1;
                strcpy(aux4->part_name,name1);

                fwrite(aux4,sizeof(ebr),1,archivo);


                fseek(archivo,st,SEEK_SET);
                globalcu=ftell(archivo);
                ebr *aux44=(ebr *)malloc(sizeof(ebr));
                fread(aux44,sizeof(ebr),1,archivo);

                fclose(archivo);


                printf("\nDatos de nueva particion logica:\n");
                printf("\nfit: %s\n",aux4->part_fit);
                printf("\nname: %s\n",aux4->part_name);
                printf("\nsiguiente: %d\n",aux4->part_next);
                printf("\ntama;o: %d\n",aux4->part_size);
                printf("\ninicio: %d\n",aux4->part_start);
                printf("\nestatus: %d\n",aux4->part_status);


          }

/****************************************************************************************************************************************************************************************************************************************************************************/


          if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
            /*  enviarebrs(path1);
              if(mbr01->mbr_partition1.part_size<logsumasize){
                  vaciarlisebr();
                  logsumasize=0;
                  printf("\nya no hay espacio para una particion tan grande.\n");
                 return -1;
              }
              vaciarlisebr();
              logsumasize=0;
*/
              int inicio =mbr01->mbr_partition4.part_start;
                int size =mbr01->mbr_partition4.part_size;

                if(size<size1){
                    printf("\nparticion logica mas grande que la extendida total\n");
                            return -1;
                }

                FILE *archivo=fopen(path1,"rb+");

                fseek(archivo,0,SEEK_SET);
                mbr *aux2 =(mbr *)malloc(sizeof(mbr));
                ebr *aux3=(ebr *)malloc(sizeof(ebr));
                fread(aux2,sizeof(mbr),1,archivo);
                fseek(archivo,inicio,SEEK_CUR);
                int cur=ftell(archivo);
                fread(aux3,sizeof(ebr),1,archivo);
                ebr *aux4=(ebr *)malloc(sizeof(ebr));
                int o;
                int contador=0;
                int st;


                int bandera=0;
                if(aux3->part_next==-1 && aux3->part_size>0){
                    aux3->part_next=aux3->part_size+aux3->part_start;

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    fwrite(aux3,sizeof(ebr),1,archivo);

                    fseek(archivo,0,SEEK_SET);

                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);
                    cur=ftell(archivo);
                    fread(aux3,sizeof(ebr),1,archivo);
                    bandera=1;
                }




               // printf("\nsiguiente de primera particion. %d\n",aux3->part_next);
               /* while(bandera==0){



                  o=aux3->part_size;
                  int lk;
                  fseek(archivo,o,SEEK_CUR);
                   contador++;

                   if(aux3->part_next==-1){

                       aux3->part_next=aux3->part_size+aux3->part_start;

                       fseek(archivo,lk,SEEK_SET);

                       fwrite(aux3,sizeof(ebr),1,archivo);

                       fseek(archivo,-sizeof(ebr),SEEK_CUR);
                       st=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);


                       break;
                   }else{
                       fseek(archivo,0,SEEK_CUR);
                         lk=ftell(archivo);
                       fread(aux3,sizeof(ebr),1,archivo);
;
                   }



                }
                bandera=0;
*/
                int lk;
                while(bandera==0){
                  o=aux3->part_size;
                   contador++;
                   if(aux3->part_next==-1){
                        aux3->part_next=aux3->part_size+aux3->part_start;
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        fwrite(aux3,sizeof(ebr),1,archivo);
                        fseek(archivo,-sizeof(ebr),SEEK_CUR);
                        st=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                        break;
                   }else{
                        fseek(archivo,o,SEEK_CUR);
                       //fseek(archivo,0,SEEK_CUR);
                        lk=ftell(archivo);
                        fread(aux3,sizeof(ebr),1,archivo);
                   }
                }
                bandera=0;

                if(aux3->part_size>0){
                fseek(archivo,aux3->part_size,SEEK_CUR);
                }else{

                    fseek(archivo,0,SEEK_SET);
                    fread(aux2,sizeof(mbr),1,archivo);
                    fseek(archivo,inicio,SEEK_CUR);

                }

                strcpy(aux4->part_fit,fit1);
                aux4->part_status=1;
                if(aux3->part_size>0){
                aux4->part_start=aux3->part_next;

                //printf("\ninicio de nueva particion. %d\n",aux4->part_start);
                }else{
                    aux4->part_start=aux2->mbr_partition4.part_start;
                  //  printf("\ninicio de nueva particion. %d",aux4->part_start);

                }
                aux4->part_size=size1;
                aux4->part_next=-1;
                strcpy(aux4->part_name,name1);

                fwrite(aux4,sizeof(ebr),1,archivo);


                fseek(archivo,st,SEEK_SET);
                globalcu=ftell(archivo);
                ebr *aux44=(ebr *)malloc(sizeof(ebr));
                fread(aux44,sizeof(ebr),1,archivo);

                fclose(archivo);


                printf("\nDatos de nueva particion logica\n");
                printf("\nfit: %s\n",aux4->part_fit);
                printf("\nname: %s\n",aux4->part_name);
                printf("\nsiguiente: %d\n",aux4->part_next);
                printf("\ntama;o: %d\n",aux4->part_size);
                printf("\ninicio: %d\n",aux4->part_start);
                printf("\nestatus: %d\n",aux4->part_status);

          }

/**************************************************************************************************************************************************************************************************************************************************************************************************************************/
      }

    }

    //SI SE ELIMINA UNA PARTICION
     if(delete11>0){
        FILE *eliminar=fopen(path1,"rb+");
        fseek(eliminar,0,SEEK_SET);
        mbr* mod=(mbr*)malloc(sizeof(mbr));
        fread(mod,sizeof(mbr),1,eliminar);
        fclose(eliminar);
        printf("\nDesea eliminar particion (si o no)\n");
        char*des[20];
        fgets(des,20,stdin);
        if(strstr(des,"no")){
            printf("\nParticion NO eliminada\n");
            return-1;
        }else if(!strstr(des,"si")){
            printf("\nRespuesta invalida, se aborto la mision.\n");
            return-1;
        }
        //PARA PARTICION UNO
        if(strcmp(mod->mbr_partition1.part_name,name1)==0){


            if(strcmp(delete1,"fast")==0){
                mod->mbr_partition1.part_status=0;
                mod->mbr_partition1.part_size=0;
                mod->mbr_partition1.part_start=0;
         strcpy(mod->mbr_partition1.part_fit,"");
         strcpy(mod->mbr_partition1.part_name,"");
         strcpy(mod->mbr_partition1.part_type,"x");


            }
            else if(strcmp(delete1,"full")==0){

                       mod->mbr_partition1.part_status=0;
                       mod->mbr_partition1.part_size=0;
                       mod->mbr_partition1.part_start=0;
                strcpy(mod->mbr_partition1.part_fit,"");
                strcpy(mod->mbr_partition1.part_name,"");
                strcpy(mod->mbr_partition1.part_type,"x");

            }else{
                printf("\nError en comando delete.\n");
                return -1;
            }
        }
        //PARA PARTICION DOS
        else if(strcmp(mod->mbr_partition2.part_name,name1)==0){
            if(strcmp(delete1,"fast")==0){
                mod->mbr_partition2.part_status=0;
                mod->mbr_partition2.part_size=0;
                mod->mbr_partition2.part_start=0;
         strcpy(mod->mbr_partition2.part_fit,"");
         strcpy(mod->mbr_partition2.part_name,"");
         strcpy(mod->mbr_partition2.part_type,"x");

            }
            else if(strcmp(delete1,"full")==0){
                       mod->mbr_partition2.part_status=0;
                       mod->mbr_partition2.part_size=0;
                       mod->mbr_partition2.part_start=0;
                strcpy(mod->mbr_partition2.part_fit,"");
                strcpy(mod->mbr_partition2.part_name,"");
                strcpy(mod->mbr_partition2.part_type,"x");

            }else{
                printf("\nError en comando delete.\n");
                return -1;
            }

        }
        //PARA PARTICION TRES
        else if(strcmp(mod->mbr_partition3.part_name,name1)==0){
            if(strcmp(delete1,"fast")==0){
                mod->mbr_partition3.part_status=0;
                mod->mbr_partition3.part_size=0;
                mod->mbr_partition3.part_start=0;
         strcpy(mod->mbr_partition3.part_fit,"");
         strcpy(mod->mbr_partition3.part_name,"");
         strcpy(mod->mbr_partition3.part_type,"x");

            }
            else if(strcmp(delete1,"full")==0){
                       mod->mbr_partition3.part_status=0;
                       mod->mbr_partition3.part_size=0;
                       mod->mbr_partition3.part_start=0;
                strcpy(mod->mbr_partition3.part_fit,"");
                strcpy(mod->mbr_partition3.part_name,"");
                strcpy(mod->mbr_partition3.part_type,"x");

            }else{
                printf("\nError en comando delete.\n");
                return -1;
            }

        }
        //PARA PARTICION CUATRO
        else if(strcmp(mod->mbr_partition4.part_name,name1)==0){
            if(strcmp(delete1,"fast")==0){


                mod->mbr_partition4.part_status=0;
                mod->mbr_partition4.part_size=0;
                mod->mbr_partition4.part_start=0;
         strcpy(mod->mbr_partition4.part_fit,"");
         strcpy(mod->mbr_partition4.part_name,"");
         strcpy(mod->mbr_partition4.part_type,"x");

            }
            else if(strcmp(delete1,"full")==0){

                       mod->mbr_partition4.part_status=0;
                       mod->mbr_partition4.part_size=0;
                       mod->mbr_partition4.part_start=0;
                strcpy(mod->mbr_partition4.part_fit,"");
                strcpy(mod->mbr_partition4.part_name,"");
                strcpy(mod->mbr_partition4.part_type,"x");

            }else{
                printf("\nError en comando delete.\n");
                return -1;
            }
        }else{
            printf("\nNOMBRE DE PARTICION NO EXISTE\n");
            return -1;
        }

        FILE *eliminar1=fopen(path1,"rb+");
        fseek(eliminar1,0,SEEK_SET);
        fwrite(mod,sizeof(mbr),1,eliminar1);
        fclose(eliminar1);
        printf("\nPARTICION ELIMINADA\n");


    }

     if(add1!=0){
        FILE *agregar=fopen(path1,"rb+");
        fseek(agregar,0,SEEK_SET);
        mbr *mod=(mbr*)malloc(sizeof(mbr));
        fread(mod,sizeof(mbr),1,agregar);
        fclose(agregar);

        if(strcmp(mod->mbr_partition1.part_name,name1)==0){

            if(Menos==0){
                int chule  = mod->mbr_partition1.part_start+mod->mbr_partition1.part_size;
                int chule0 =chule+add1;
                int chule1 = mod->mbr_partition2.part_start;
                int chule2 = mod->mbr_partition3.part_start;
                int chule3 = mod->mbr_partition4.part_start;

                int britany1 = mod->mbr_partition2.part_size;
                int britany2 = mod->mbr_partition3.part_size;
                int britany3 = mod->mbr_partition4.part_size;

                int brayan =mod->mbr_tamanio;


                if(chule1>chule && (chule1<chule2 || britany2<=0) && (chule1<chule3 || britany3<=0) ){
                    if(chule0<chule1){
                     mod->mbr_partition1.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule2>chule && (chule2<chule1 || britany1<=0) && (chule2<chule3 || britany3<=0) ){
                    if(chule0<chule2){
                     mod->mbr_partition1.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }


                }else if(chule3>chule && (chule3<chule1 || britany1<=0) && (chule3<chule2 || britany2<=0) ){
                    if(chule0<chule3){
                     mod->mbr_partition1.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule0<brayan){


                     mod->mbr_partition1.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");



                }

            }

            else if(Menos!=0){
                int tam   =mod->mbr_partition1.part_size;
                int valor =tam-add1;
                if(valor>0){
                    mod->mbr_partition1.part_size=valor;
                    FILE *betzy = fopen(path1,"rb+");
                    fseek(betzy,0,SEEK_SET);
                    fwrite(mod,sizeof(mbr),1,betzy);
                    fclose(betzy);
                    printf("\nESPACIO MODIFICADO\n");


                }else{
                    printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                    return -1;
                }

            }else{
                printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                return -1;
            }

        }
        else if(strcmp(mod->mbr_partition2.part_name,name1)==0){

            if(Menos==0){
                int chule  = mod->mbr_partition2.part_start+mod->mbr_partition2.part_size;
                int chule0 =chule+add1;
                int chule1 = mod->mbr_partition1.part_start;
                int chule2 = mod->mbr_partition3.part_start;
                int chule3 = mod->mbr_partition4.part_start;

                int britany1 = mod->mbr_partition1.part_size;
                int britany2 = mod->mbr_partition3.part_size;
                int britany3 = mod->mbr_partition4.part_size;

                int brayan =mod->mbr_tamanio;


                if(chule1>chule && (chule1<chule2 || britany2<=0) && (chule1<chule3 || britany3<=0) ){
                    if(chule0<chule1){
                     mod->mbr_partition2.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule2>chule && (chule2<chule1 || britany1<=0) && (chule2<chule3 || britany3<=0) ){
                    if(chule0<chule2){
                     mod->mbr_partition2.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }


                }else if(chule3>chule && (chule3<chule1 || britany1<=0) && (chule3<chule2 || britany2<=0) ){
                    if(chule0<chule3){
                     mod->mbr_partition2.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule0<brayan){


                     mod->mbr_partition2.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");


                }

            }

            else if(Menos!=0){
                int tam   =mod->mbr_partition2.part_size;
                int valor =tam-add1;
                if(valor>0){
                    mod->mbr_partition2.part_size=valor;
                    FILE *betzy = fopen(path1,"rb+");
                    fseek(betzy,0,SEEK_SET);
                    fwrite(mod,sizeof(mbr),1,betzy);
                    fclose(betzy);
                    printf("\nESPACIO MODIFICADO\n");


                }else{
                    printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                    return -1;
                }

            }else{
                printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                return -1;
            }

        }
        else if(strcmp(mod->mbr_partition3.part_name,name1)==0){
            if(Menos==0){
                int chule  = mod->mbr_partition3.part_start+mod->mbr_partition3.part_size;
                int chule0 =chule+add1;
                int chule1 = mod->mbr_partition2.part_start;
                int chule2 = mod->mbr_partition1.part_start;
                int chule3 = mod->mbr_partition4.part_start;

                int britany1 = mod->mbr_partition2.part_size;
                int britany2 = mod->mbr_partition1.part_size;
                int britany3 = mod->mbr_partition4.part_size;

                int brayan =mod->mbr_tamanio;


                if(chule1>chule && (chule1<chule2 || britany2<=0) && (chule1<chule3 || britany3<=0) ){
                    if(chule0<chule1){
                     mod->mbr_partition3.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule2>chule && (chule2<chule1 || britany1<=0) && (chule2<chule3 || britany3<=0) ){
                    if(chule0<chule2){
                     mod->mbr_partition3.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }


                }else if(chule3>chule && (chule3<chule1 || britany1<=0) && (chule3<chule2 || britany2<=0) ){
                    if(chule0<chule3){
                     mod->mbr_partition3.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if( chule0<brayan){


                     mod->mbr_partition3.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");



                }

            }

            else if(Menos!=0){
                int tam   =mod->mbr_partition3.part_size;
                int valor =tam-add1;
                if(valor>0){
                    mod->mbr_partition3.part_size=valor;
                    FILE *betzy = fopen(path1,"rb+");
                    fseek(betzy,0,SEEK_SET);
                    fwrite(mod,sizeof(mbr),1,betzy);
                    fclose(betzy);
                    printf("\nESPACIO MODIFICADO\n");


                }else{
                    printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                    return -1;
                }

            }else{
                printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                return -1;
            }

        }
        else if(strcmp(mod->mbr_partition4.part_name,name1)==0){

            if(Menos==0){
                int chule  = mod->mbr_partition4.part_start+mod->mbr_partition4.part_size;
                int chule0 =chule+add1;
                int chule1 = mod->mbr_partition2.part_start;
                int chule2 = mod->mbr_partition3.part_start;
                int chule3 = mod->mbr_partition1.part_start;

                int britany1 = mod->mbr_partition2.part_size;
                int britany2 = mod->mbr_partition3.part_size;
                int britany3 = mod->mbr_partition1.part_size;

                int brayan =mod->mbr_tamanio;


                if(chule1>chule && (chule1<chule2 || britany2<=0) && (chule1<chule3 || britany3<=0) ){
                    if(chule0<chule1){
                     mod->mbr_partition4.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule2>chule && (chule2<chule1 || britany1<=0) && (chule2<chule3 || britany3<=0) ){
                    if(chule0<chule2){
                     mod->mbr_partition4.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }


                }else if(chule3>chule && (chule3<chule1 || britany1<=0) && (chule3<chule2 || britany2<=0) ){
                    if(chule0<chule3){
                     mod->mbr_partition4.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;
                    }else{
                        printf("\nNo hay suficiente espacio libre para agrandar la particion\n");
                        return -1;
                    }
                }else if(chule0<brayan){


                     mod->mbr_partition4.part_size=chule0;
                     FILE *betzy = fopen(path1,"rb+");
                     fseek(betzy,0,SEEK_SET);
                     fwrite(mod,sizeof(mbr),1,betzy);
                     fclose(betzy);
                     printf("\nESPACIO MODIFICADO\n");
                     return -1;


                }

            }

            else if(Menos!=0){
                int tam   =mod->mbr_partition4.part_size;
                int valor =tam-add1;
                if(valor>0){
                    mod->mbr_partition4.part_size=valor;
                    FILE *betzy = fopen(path1,"rb+");
                    fseek(betzy,0,SEEK_SET);
                    fwrite(mod,sizeof(mbr),1,betzy);
                    fclose(betzy);
                    printf("\nESPACIO MODIFICADO\n");


                }else{
                    printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                    return -1;
                }

            }else{
                printf("\nNo hay suficiente espacio libre para modificar la particion\n");
                return -1;
            }
        }else{
            printf("\nNOMBRE DE PARTICION NO EXISTE\n");
            return -1;
        }


    }

    return 1;
}
int IniciarParticion(int a1,int a2, int b1, int b2, int c1, int c2, int size, int sizedisco){
    //a1, b1 ,c1 son los inicios de las particiones, y a2, b2, c2 son el size de cada particion
    int aux1;
    int ref=-10;

    int cero   =-1;
    int uno    =-1;
    int dos    =-1;
    int tres   =-1;
    int cuatro =-1;
    int cinco  =-1;
    int seis   =-1;
    int siete  =-1;
    int nueve  =-1;
    int diez   =-1;
    int once   =-1;
    int doce   =-1;

    int arr[15];
    arr[1]=cero;
    arr[2]=uno;
    arr[3]=dos;
    arr[4]=tres;
    arr[5]=cuatro;
    arr[6]=cinco;
    arr[7]=seis;
    arr[8]=siete;
    arr[9]=nueve;
    arr[10]=diez;
    arr[11]=once;
    arr[12]=doce;
    //printf("\nvalor a2: %d\n",a2);
    if(a2==0 && b2==0 && c2==0){
          return 0;
      }
    if((a1<=b1 || b2<1) && (a1<=c1|| c2<1) && a2>0){
        /**************PARA A MENOR***********************************/
        ref=1;
        if(size<=a1){
            cero =0;
            arr[1]=a1;
        }
        if(size<=a1){
            return 0;
        }
        if((b1<c1 ||c2<=0) && b2>0){//MODIFIQUE PUSE LOS IGUALES

            /***********************************************/

            aux1=b1-(a1+a2);
            if(size<=aux1 ){
                uno= a1+a2;
                arr[2]=aux1;
            }

            if(c2<=0){
             aux1=sizedisco-(b1+b2);
             if(size<=aux1){
                 arr[3]=aux1;
                dos =b1+b2;
             }

            }else{
                aux1=c1-(b1+b2);
                if(size<=aux1){
                    tres =b1+b2;
                    arr[4]=aux1;
                }else if((sizedisco-c1-c2)>=size){
                    tres =c1+c2;
                    arr[4]=sizedisco-c1-c2;
                }

            }

            /**************************************/


        }
        if((c1<b1 || b2<=0) && c2>0){

            /*************************************/
            aux1=c1-(a1+a2);
            if(size<=aux1 ){
                cuatro= a1+a2;
                arr[5]=aux1;
            }

            if(b2<=0){
             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                cinco =c1+c2;
                arr[6]=aux1;
             }

            }else{
                aux1=b1-(c1+c2);
                if(size<=aux1){
                    seis =c1+c2;
                    arr[7]=aux1;
                }else if((sizedisco-b1-b2)>=size){
                    seis =b1+b2;
                    arr[7]=sizedisco-b1-b2;
                }
            }


            /************************************/


        }
        if(c2>0 && b2<=0){

            /*************************************/
            aux1=c1-(a1+a2);
            if(size<=aux1 ){
                nueve= a1+a2;//crear variable int nueve;
                arr[9]=aux1;
            }

             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                diez =c1+c2;//crear variable int diez
                arr[10]=aux1;
             }

            /************************************/
            }
        if(b2>0 && c2<=0){

                    /*************************************/
                    aux1=b1-(a1+a2);
                    if(size<=aux1 ){
                        once= a1+a2;//crear variable int once;
                        arr[11]=aux1;
                    }

                     aux1=sizedisco-(b1+b2);
                     if(size<=aux1){
                        doce =b1+b2;//crear variable int doce
                        arr[12]=aux1;
                     }

                    /************************************/
                    }
         aux1= sizedisco-(a1+a2);
        if(size<=aux1 && b2<=0 && c2<=0){
                siete =a1+a2;
                arr[8]=aux1;
            }

        /**************FIN A MENOR***********************************/
    }
    else if((b1<=a1|| a2<1) && (b1<=c1 || c2<1) && b2>0){
        /**************PARA B MENOR***********************************/
        ref=1;
        if(size<=b1){
                cero=0;
               arr[1]=b1;
        }
        if(size<=b1 ){
            return 0;
        }
        if((a1<c1 || c2<=0) && a2>0){

            /***********************************************/

            aux1=(a1)-(b1+b2);
            if(size<=aux1 ){
                uno= b1+b2;
                arr[2]=aux1;
            }

            if(c2<=0){
             aux1=sizedisco-(a1+a2);
             if(size<=aux1){
                dos =a1+a2;
                arr[3]=aux1;
             }

            }else{
                aux1=c1-(a1+a2);
                if(size<=aux1){
                    tres =a1+a2;
                    arr[4]=aux1;
                }else if((sizedisco-c1-c2)>=size){
                    tres =c1+c2;
                    arr[4]=sizedisco-c1-c2;
                }

            }

            /**************************************/


        }
        if((c1<a1 || a2<=0)&& c2>0){

            /*************************************/
            aux1=(c1)-(b1+b2);
            if(size<=aux1 ){
                cuatro= b1+b2;
                arr[5]=aux1;
            }

            if(a2<=0){
             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                cinco =c1+c2;
                arr[6]=aux1;
             }

            }else{
                aux1=a1-(c1+c2);
                if(size<=aux1){
                    seis =c1+c2;
                    arr[7]=aux1;
                }else if((sizedisco-a1-a2)>=size){
                    seis =a1+a2;
                    arr[4]=sizedisco-a1-a2;
                }

               }

            /************************************/


        }
        if(c2>0 && a2<=0){

            /*************************************/
            aux1=c1-(b1+b2);
            if(size<=aux1 ){
                nueve= b1+b2;//crear variable int nueve;
                arr[9]=aux1;
            }

             aux1=sizedisco-(c1+c2);
             if(size<=aux1){
                diez =c1+c2;//crear variable int diez
                arr[10]=aux1;
             }

            /************************************/
            }
        if(a2>0 && c2<=0){

                    /*************************************/
                    aux1=a1-(b1+b2);
                    if(size<=aux1 ){
                        once= a1+a2;//crear variable int once;
                        arr[11]=aux1;
                    }

                     aux1=sizedisco-(a1+a2);
                     if(size<=aux1){
                        doce =a1+a2;//crear variable int doce
                        arr[12]=aux1;
                     }

                    /************************************/
                    }
        aux1= sizedisco-(b1+b2);
        if(size<=aux1 && a2<=0 && c2<=0){
                siete =b1+b2;
                arr[8]=aux1;
            }



        /**************FIN B MENOR***********************************/

    }
    else if((c1<=a1|| a2<1) && (c1<=b1|| b2<1) && c2>0){

        /**************PARA C MENOR***********************************/
        ref=1;
        if(size<=c1){
                cero=0;
                arr[1]=aux1;
        }
        if(size<=c1 ){
            return 0;
        }
        if((a1<b1 || b2<=0) && a2>0){

            /***********************************************/

            aux1=(a1)-(c1+c2);
            if(size<=aux1 ){
                uno= c1+c2;
                arr[2]=aux1;
            }

            if(b2<=0){
             aux1=sizedisco-(a1+a2);
             if(size<=aux1){
                dos =a1+a2;
                arr[3]=aux1;
             }

            }else{
                aux1=b1-(a1+a2);
                if(size<=aux1){
                    tres =a1+a2;
                    arr[4]=aux1;
                }else if((sizedisco-b1-b2)>=size){
                    tres =b1+b2;
                    arr[4]=sizedisco-b1-b2;
                }
            }


            /**************************************/


        }
        if((b1<a1 || a2<=0)&& b2>0){

            /*************************************/
            aux1=(b1)-(c1+c2);
            if(size<=aux1 ){
                cuatro= c1+c2;
                arr[5]=aux1;
            }

            if(a2<=0){
             aux1=sizedisco-(b1+b2);
             if(size<=aux1){
                cinco =b1+b2;
                arr[6]=aux1;
             }

            }else{
                aux1=a1-(b1+b2);
                if(size<=aux1){
                    seis =b1+b2;
                    arr[7]=aux1;
                }else if((sizedisco-a1-a2)>=size){
                    seis =a1+a2;
                    arr[4]=sizedisco-a1-a2;
                }

            }

            /************************************/


        }
        if(b2>0 && a2<=0){

                    /*************************************/
                    aux1=b1-(c1+c2);
                    if(size<=aux1 ){
                        nueve= c1+c2;//crear variable int nueve;
                        arr[9]=aux1;
                    }

                     aux1=sizedisco-(b1+b2);
                     if(size<=aux1){
                        diez =b1+b2;//crear variable int diez
                        arr[10]=aux1;
                     }

                    /************************************/
                    }
        if(a2>0 && b2<=0){

                            /*************************************/
                            aux1=a1-(c1+c2);
                            if(size<=aux1 ){
                                once= a1+a2;//crear variable int once;
                                arr[11]=aux1;
                            }

                             aux1=sizedisco-(a1+a2);
                             if(size<=aux1){
                                doce =a1+a2;//crear variable int doce
                                arr[12]=aux1;
                             }

                            /************************************/
                            }
        aux1= (c1+c2)-sizedisco;
        if(size<=aux1 && a2<=0 && b2<=0){
                siete =c1+c2;
                arr[8]=aux1;
            }



        /**************FIN C MENOR***********************************/
    }
    else{
        printf("\nError al crear el disco\n");
        return -1;
    }
     int u[15];
     u[1]=cero;
     u[2]=uno;
     u[3]=dos;
     u[4]=tres;
     u[5]=cuatro;
     u[6]=cinco;
     u[7]=seis;
     u[8]=siete;
     u[9]=nueve;
     u[10]=diez;
     u[11]=once;
     u[12]=doce;
     int l=1;
     for(l;l<13;l++){
         //printf("\n--------------------------------------------------valor de espacio: %d  valor de l: %d\n",arr[l],l);
     }
    // printf("\n-----------------------------------------------------------valor de size: %d\n",size);



                int n=1;
                int auxiliar =-1;
                int auxiliar2=-1;
                int auxiliar3=-1;
                int auxiliar4=-1;

                for(n;n<=11;n++){

                    if(size<=arr[n] && arr[n]!=-1){
                       auxiliar4=auxiliar3;
                       auxiliar3=u[n];
                       if(auxiliar3<auxiliar4 || auxiliar4==-1){
                           auxiliar =arr[n];
                           auxiliar2=u[n];
                       }else{
                           auxiliar =1;
                           auxiliar2=auxiliar4;
                       }

                    }
                }

                if(auxiliar!=-1){
                 return auxiliar2;
                }else{printf("\nEspacio fragmentado insuficiente para contener esta particion.\n"); return -1;}


}
int mount(char*token){

if((strstr(comprobarcadena,"\"/") && strstr(comprobarcadena,".dsk\"") )|| (strcmp(comprobarcadena,"mount")==0)){
    }else{printf("\nError en el comando\n"); return -1;}

int mostrar=0;
    if(strstr(comprobarcadena,"path") && strstr(comprobarcadena,"name")){}

    else{
    int tm1=re->tam;
     registro *ho=(registro*)malloc(sizeof(registro));
     ho=re->primero;
     while(tm1>=1){
         printf("\nMONTADA: id: %s  name: %s    path: %s \n",ho->id,ho->name,ho->path);
         ho=ho->siguiente;
         tm1--;

     }
     return 0;
     }
    int op =0;
    char *name1[50];
    char *path1[200];
    while(token !=NULL){
        //printf("\nentro a while\n");
        token=strtok(NULL," :");
        if(token==NULL) break;

        if(strstr(token,"-path"))    op=1;
        if(strstr(token,"-name"))    op=2;
     switch(op){
      case 1:
            token=strtok(NULL,":\"\n");
         // token = strtok(NULL," :");
      strcpy(path1,"/");
      char *tok;
      if(strstr(token,"\"")){
        //tok=strtok(token,"\"");
        strcpy(path1,tok);
      }else{
          strcpy(path1,token);
      }
      //printf("el path es: %s",path1);
      FILE* comprobar =fopen(path1,"r");
      if(comprobar){
      fclose(comprobar);
      }else{
      printf("\nArchivo Inexistente\n");
      return -1;
      }

          break;
      case 2:
       //   token =strtok(NULL," :");
         token=strtok(NULL,":\"\n");
          strcpy(name1,token);
        //  printf("\nEl nombre es: %s\n",name1);
          if(name1==NULL){
              printf("\nNombre invalido\n");
              return -1;
          }
          break;

      default:
          printf("\ncomandos invalidos\n");
          return -1;
          break;

        }


    }

     FILE *archivo =fopen(path1,"rb+");
     fseek(archivo,0,SEEK_SET);
     mbr*aux =(mbr*)malloc(sizeof(mbr));
     fread(aux,sizeof(mbr),1,archivo);
     fclose(archivo);
     if(archivo){
         //printf("\nabrio archivo\n");
     if(strcmp(aux->mbr_partition1.part_name,name1)==0 || strcmp(aux->mbr_partition2.part_name,name1)==0 || strcmp(aux->mbr_partition3.part_name,name1)==0 ||strcmp(aux->mbr_partition4.part_name,name1)==0){
         registro* nuevo =(registro*)malloc(sizeof(registro));
         strcpy(nuevo->name,name1);
         strcpy(nuevo->path,path1);
         char *id11[10];
         if(re->tam==0){
             strcpy(nuevo->id,"vda1");
         }else{
             registro* nodo =(registro*)malloc(sizeof(registro));
             nodo=re->primero;
             int rec=re->tam;

             registro* nodo123 =(registro*)malloc(sizeof(registro));
             nodo123=re->primero;
             int rec123=re->tam;


             int existe=0;
             char *vd[10];//letra del id
             int  *num;//numero que corresponde al id
             char *to;
             char* to2;


             while(rec>=1){
                 if(strcmp(nodo->path,path1)==0){
                     addlista(nodo->id);

                     char *superid[20];
                     strcpy(superid,nodo->id);
                     to=strtok(superid,"vd1234567890");

                     if(to==NULL){
                         char *superid1[20];
                         strcpy(superid1,nodo->id);
                         to2=strtok(superid1,"v");
                         if(strstr(to2+1,"d")==0){
                             strcpy(vd,"d");
                         }else{
                             strcpy(vd,"v");
                         }
                     }else{
                     strcpy(vd,to);
                     }


                     existe=1;
                 }
                nodo =nodo->siguiente;
                    rec--;
             }
             num = traernumero();
             vaciarlista();

             if(existe==0){
              //   printf("\nid uno en existe 0: %s\n",re->primero->id);
                 nodo=re->primero;
                 rec=re->tam;
                 char* vd1[10];
                 int ban[30];
                 int i=0;
                 //printf("\nid uno en existe 0.1: %s\n",re->primero->id);
                 for(i;i<=30;i++){
                     ban[i]=-1;
                 }
                 int ii=0;
                for(ii;ii<=30;ii++){
               // printf("\ntodos menos uno valo de ban en %d:    %d \n",ii,ban[ii]);
                }
                 while(rec>=1){
                     char *superid3[20];
                     strcpy(superid3,nodo->id);
                     to=strtok(superid3,"vd1234567890");

                     if(to==NULL){
                         char *superid4[20];
                         strcpy(superid4,nodo->id);
                         to2=strtok(superid4,"v");
                         if(strstr(to2+1,"d")==0){
                             strcpy(vd1,"d");
                         }else{
                             strcpy(vd1,"v");
                         }
                     }else{
                     strcpy(vd1,to);
                    // printf("\nletra ya existe: %s\n",vd1);
                     }

                     if(strcmp(vd1,"a")==0){ ban [1]=1;};
                     if(strcmp(vd1,"b")==0){ ban [2]=1;};
                     if(strcmp(vd1,"c")==0){ ban [3]=1;};
                     if(strcmp(vd1,"d")==0){ ban [4]=1;};
                     if(strcmp(vd1,"e")==0){ ban [5]=1;};
                     if(strcmp(vd1,"f")==0){ ban [6]=1;};
                     if(strcmp(vd1,"g")==0){ ban [7]=1;};
                     if(strcmp(vd1,"h")==0){ ban [8]=1;};
                     if(strcmp(vd1,"i")==0){ ban [9]=1;};
                     if(strcmp(vd1,"j")==0){ ban [10]=1;};
                     if(strcmp(vd1,"k")==0){ ban [11]=1;};
                     if(strcmp(vd1,"l")==0){ ban [12]=1;};
                     if(strcmp(vd1,"m")==0){ ban [13]=1;};
                     if(strcmp(vd1,"n")==0){ ban [14]=1;};
                     if(strcmp(vd1,"o")==0){ ban [15]=1;};
                     if(strcmp(vd1,"p")==0){ ban [16]=1;};
                     if(strcmp(vd1,"q")==0){ ban [17]=1;};
                     if(strcmp(vd1,"r")==0){ ban [18]=1;};
                     if(strcmp(vd1,"s")==0){ ban [19]=1;};
                     if(strcmp(vd1,"t")==0){ ban [20]=1;};
                     if(strcmp(vd1,"u")==0){ ban [21]=1;};
                     if(strcmp(vd1,"v")==0){ ban [22]=1;};
                     if(strcmp(vd1,"w")==0){ ban [23]=1;};
                     if(strcmp(vd1,"x")==0){ ban [24]=1;};
                     if(strcmp(vd1,"y")==0){ ban [25]=1;};
                     if(strcmp(vd1,"z")==0){ ban [26]=1;};


                    nodo =nodo->siguiente;
                        rec--;
                 }

                 int iii=1;
                for(iii;iii<=30;iii++){
             //   printf("\nsolo el 2 debe dar uno %d:    %d \n",iii,ban[iii]);
                }
                 int j=1;
                 int guarda;
                 for(j;j<29;j++){

                     if(ban[j]==-1){
                     guarda=j;
                    // printf("\nvalor de guarda: %d\n",guarda);
                     break;
                     }
                 }



                      if(guarda==1){strcpy(vd,"a");}
                 else if(guarda==2){strcpy(vd,"b");}
                 else if(guarda==3){strcpy(vd,"c");}
                 else if(guarda==4){strcpy(vd,"d");}
                 else if(guarda==5){strcpy(vd,"e");}
                 else if(guarda==6){strcpy(vd,"f");}
                 else if(guarda==7){strcpy(vd,"g");}
                 else if(guarda==8){strcpy(vd,"h");}
                 else if(guarda==9){strcpy(vd,"i");}
                 else if(guarda==10){strcpy(vd,"j");}
                 else if(guarda==11){strcpy(vd,"k");}
                 else if(guarda==12){strcpy(vd,"l");}
                 else if(guarda==13){strcpy(vd,"m");}
                 else if(guarda==14){strcpy(vd,"n");}
                 else if(guarda==15){strcpy(vd,"o");}
                 else if(guarda==16){strcpy(vd,"p");}
                 else if(guarda==17){strcpy(vd,"q");}
                 else if(guarda==18){strcpy(vd,"r");}
                 else if(guarda==19){strcpy(vd,"s");}
                 else if(guarda==20){strcpy(vd,"t");}
                 else if(guarda==21){strcpy(vd,"u");}
                 else if(guarda==22){strcpy(vd,"v");}
                 else if(guarda==23){strcpy(vd,"w");}
                 else if(guarda==24){strcpy(vd,"x");}
                 else if(guarda==25){strcpy(vd,"y");}
                 else if(guarda==26){strcpy(vd,"z");}

             }
             char cadena1[10];

            // printf("\nnumero justo antes de pasarlo: %d\n",num);
             if(existe==0){
             sprintf(cadena1, "%d", 1);
             }else{

                 sprintf(cadena1, "%d", num);
             }
           //  printf("\nnumero justo despues de pasarlo: %s\n",cadena1);
             strcpy(id11,"vd");
             strcat(id11,vd);
             strcat(id11,cadena1);
             strcpy(nuevo->id,id11);
             printf("\nid de la nueva montada:  %s\n",nuevo->id);

         }
         nuevo->anterior=NULL;
         nuevo->siguiente=NULL;


         if(re->tam==0){
             re->primero=re->ultimo=nuevo;
             re->tam++;
         }
         else{
             nuevo->anterior=re->ultimo;
            re->ultimo->siguiente=nuevo;
            re->ultimo=nuevo;
            re->tam++;

         }

     }else{
         printf("\nParticion solicitada no existe\n");
         return -1;
     }

    }

     int tm1=re->tam;
     registro *ho=(registro*)malloc(sizeof(registro));
     ho=re->primero;
     while(tm1>=1){
         printf("\nMONTADA: id: %s  name: %s    path: %s \n",ho->id,ho->name,ho->path);
         ho=ho->siguiente;
         tm1--;

     }
     return 0;

}
int umount(char*token){

    if(strstr(comprobarcadena,"id")){ }else{printf("\nError en comando;\n"); return -1;}

    int op =0;
    char *id1[50];
    while(token !=NULL){
        token=strtok(NULL," :");

        if(token==NULL) break;

        if(strstr(token,"-id"))    op=1;
         switch(op){
            case 1:
             token = strtok(NULL," :");
             strcpy(id1,token);

    registro* aux =(registro *)malloc(sizeof(registro));
    registro* aux1 =(registro *)malloc(sizeof(registro));
    registro* aux2 =(registro *)malloc(sizeof(registro));
    aux=re->primero;
    int n=re->tam;
    int encontrado=0;
    while(n>=1){

        if(strcmp(id1,aux->id)==0){
            encontrado=1;
            break;
        }
        aux=aux->siguiente;
        n--;
    }
    //printf("\nid de auxilair: %s\n",aux->id);
    if(encontrado==1){

      if(re->tam>1){
           if(aux->siguiente==NULL){
                 aux1->anterior=NULL;
              }else{aux1=aux->siguiente;}


            if(aux->anterior==NULL){
                 aux2->siguiente=NULL;
             }else{aux2=aux->anterior;}

             re->tam--;

            if(aux1->anterior==NULL){}
            else{aux1->anterior=aux2;}

            if(aux2->siguiente==NULL){}
            else{aux2->siguiente=aux1;}

       //------------------------------
       if(re->primero==aux){
           re->primero=aux->siguiente;
       }
       else if(re->ultimo==aux){
           re->ultimo=aux->anterior;
       }//-----------------------
      free(aux);
       }else{
           re->primero=NULL;
           re->ultimo=NULL;
           re->tam=0;
           free(aux);
       }

    }else{printf("\nNo existe una particion montada con ese id\n");}


          //   printf("\nel id es: %s\n",id1);
             break;

         default:
          printf("\ncomandos invalidos\n");
          return -1;
          break;
        }
    }





    int tm1=re->tam;
    registro *ho=(registro*)malloc(sizeof(registro));
    ho=re->primero;
    while(tm1>=1){
        printf("\nMONTADA: id: %s  name: %s    path: %s \n",ho->id,ho->name,ho->path);
        ho=ho->siguiente;
        tm1--;

    }
    return 0;

}
void addlista(char* id[20]){
    char *tok;
     nodolista *nuevo=(nodolista*)malloc(sizeof(nodolista));
     nuevo->anterior=(nodolista*)malloc(sizeof(nodolista));
     nuevo->siguiente=(nodolista*)malloc(sizeof(nodolista));
     nuevo->anterior=NULL;
     nuevo->siguiente=NULL;
     tok=strtok(id,"abcdefghijklmnopqrstuvwxyz");
     int numero =atoi(tok);
     nuevo->numero=numero;
     int tam= listanumeros->tam;

     if(tam==0){
         listanumeros->primero=listanumeros->ultimo=nuevo;
         listanumeros->tam++;
     }else{
         nuevo->anterior=listanumeros->ultimo;
        listanumeros->ultimo->siguiente=nuevo;
        listanumeros->ultimo=nuevo;
        listanumeros->tam++;
     }

}
int traernumero(){
int aux1=1;
int tam =listanumeros->tam;

nodolista* auxiliar =(nodolista*)malloc(sizeof(nodolista));
auxiliar=listanumeros->primero;

    while(tam>=1){
        if(auxiliar->numero ==aux1){
            aux1++;
        }
        auxiliar=auxiliar->siguiente;
        tam--;
    }
    return aux1;
}
void vaciarlista(){
    listanumeros->primero=NULL;
    listanumeros->ultimo=NULL;
    listanumeros->tam=0;
}
int rep(char *token){
/********************************************************************************************************************************************************************/
    if(strstr(comprobarcadena,"\"/") && strstr(comprobarcadena,"\"")){
    }else{printf("\nError en el comando\n"); return -1;}
    int    op = 0;
    char*  path1[200];
    char*  name1[50];
    char*  id1[20];

    char dpth[200];
    char dpth2[200];
    char dpth3[200];



       if(strstr(comprobarcadena,"-path") && strstr(comprobarcadena,"-name") && strstr(comprobarcadena,"-id")){

       }else{
           printf("\nFalta Informacion\n");
       return -1;
       }
       if(strstr(comprobarcadena,"mbr") || strstr(comprobarcadena,"disk") ){

       }else{
           printf("\nnombre de reporte no especificado.\n");
       return -1;
       }

    while(token !=NULL){
        token=strtok(NULL," :");
        if(token==NULL) break;
        if(strstr(token,"-path"))    op=1;
        if(strstr(token,"-name"))    op=2;
        if(strstr(token,"-id"))    op=3;
     switch(op){
      case 1:

        token=strtok(NULL,":\"\n");
        if(strstr(token,"\"")){
           // printf("token3  ------%s\n",token);
            strcpy(dpth,token);
            strcpy(dpth2,dpth);
            strcpy(dpth3,dpth);
        }else{
            //token = strtok(NULL,":");
            strcpy(dpth,token);
            strcpy(dpth2,token);
            strcpy(dpth3,token);
        }


      //  printf("dpth %s\n",dpth);
       // printf("dpth2 %s\n",dpth2);
       // printf("dpth3 %s\n",dpth3);

        break;

       /*  token = strtok(NULL," :");

         if(strstr(token,"\"")){
             strcpy(dpth,token+1);
             token=strtok(NULL,"\"");
             strcat(dpth," ");
             strcat(dpth,token);
             strcpy(dpth2,dpth);
             strcpy(dpth3,dpth);
         }else{
             strcpy(dpth,token);
             strcpy(dpth2,token);
             strcpy(dpth3,token);
         }
         break;*/

      case 2:

      token=strtok(NULL,":\"\n");
        if(strstr(token,"\"")){
           // printf("token3  ------%s\n",token);
            strcpy(name1,token);
        }else{
            //token = strtok(NULL,":");
            strcpy(name1,token);
        }

      /******************************/
         // token =strtok(NULL," :");
       //   strcpy(name1,token);


          if(name1==NULL){
              printf("\nNombre invalido\n");
              return -1;
          }
          break;

     case 3:
         token =strtok(NULL," :");
         strcpy(id1,token);
         if(id1==NULL){
             printf("\nid invalido\n");
             return -1;
         }
         break;

      default:
          printf("\ncomandos invalidos\n");
          return -1;
          break;

        }

    }
        //printf("\n--path: %s path: %s\n",dpth3,dpth);

    /********************CREANDO PATH***********************/
    //creando path
     //SE CREA EL PATH

    //strcat(dpth,Nombre);
    //strcat(dpth2,Nombre);
    //strcat(dpth3,Nombre);
    int numPalabras =1;
    char *tem;
    tem =strtok(dpth,"/");

    while(tem!=NULL){
        tem =strtok(NULL,"/");
        if(tem==NULL) break;
        numPalabras++;
    }

    char pathReal[200]="/";
    char*aux11;
    aux11= strtok(dpth2,"/");
    strcat(pathReal,aux11);
    strcat(pathReal,"/");
    while(numPalabras > 2)
    {
        aux11 = strtok(NULL,"/");
        strcat(pathReal,aux11);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    aux11 = strtok(NULL,"/");
  /*  int numPalabras =1;
    char *tem;
    tem =strtok(dpth,"/");

    while(tem!=NULL){
        tem =strtok(NULL,"/");
        if(tem==NULL) break;
        numPalabras++;
    }

    char pathReal[200]="/";
    char*aux11;
    aux11= strtok(dpth2,"/");
    strcat(pathReal,aux11);
    strcat(pathReal,"/");
    while(numPalabras > 2)
    {
        aux11 = strtok(NULL,"/");
        strcat(pathReal,aux11);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    aux11 = strtok(NULL,"/");*/
        /********************FN DE CREAR PATH***********************/

    /********************VERIFICAR EXISTENCIA DE ID***********************/
    registro* aux1=(registro*)malloc(sizeof(registro));
    aux1=re->primero;
    int tam = re->tam;
    if(tam==0){
    printf("\nNo hay particiones montadas.\n");
    return -1;
    }
        while(tam>=1){

            if(strcmp(aux1->id,id1)==0){
                break;
            }
            aux1=aux1->siguiente;
            tam--;
            if(tam==0){printf("\nNo se encontro el id\n"); return -1;}
        }




    /********************FIN DE VERIFICAR EXISTENCIA DE ID***********************/
    /********************TRAYENDO EL DISCO COMPLETO Y CARGAR TODAS SUS PARTICIONES****************************/
        mbr* cargambr=(mbr*)malloc(sizeof(mbr));
        FILE*disco=fopen(aux1->path,"rb+");
        fseek(disco,0,SEEK_SET);
        fread(cargambr,sizeof(mbr),1,disco);
        //("--lllllllllllllllllllllll--------------------%s\n",cargambr->mbr_partition1.part_type);
        //printf("\nname1: %s\n",name1);

        if(strcmp(name1,"mbr")==0 ||strcmp(name1,"disk")==0){
            enviarebrs(aux1->path);
            reportedisk* crea =(reportedisk*)malloc(sizeof(reportedisk));
            int ext=0;
            int h=4;
            int contador =1;
            /****Agregando el mbr a la lista de reporte disk***************/
                  crea->anterior==NULL;
                  crea->siguiente==NULL;
                  strcpy(crea->mbr_fecha_creacion,cargambr->mbr_fecha_creacion);
                  crea->mbr_tamanio=cargambr->mbr_tamanio;
                  crea->EsMbr=1;
                  if(reportedisk1->tam==0){
                      reportedisk1->primero=reportedisk1->ultimo=crea;
                      reportedisk1->tam++;
                     // printf("\nmbr: agregado\n");
                  }
            /****Fin de agregar el mbr a la lista de reporte disk**********/

            while(h>0){
                if(contador==1 && cargambr->mbr_partition1.part_size>0){
                   // printf("\nnombre de la particion 1: %s\n",cargambr->mbr_partition1.part_name);
                    addlistareportedisk(cargambr->mbr_partition1);
                    if(strcmp(cargambr->mbr_partition1.part_type,"e")==0){ext=1;};
                }
                if(contador==2 && cargambr->mbr_partition2.part_size>0){
                    addlistareportedisk(cargambr->mbr_partition2);
                    if(strcmp(cargambr->mbr_partition2.part_type,"e")==0){ext=2;};
                }
                if(contador==3 && cargambr->mbr_partition3.part_size>0){
                    addlistareportedisk(cargambr->mbr_partition3);
                    if(strcmp(cargambr->mbr_partition3.part_type,"e")==0){ext=3;};
                }
                if(contador==4 && cargambr->mbr_partition4.part_size>0){
                    addlistareportedisk(cargambr->mbr_partition4);
                    if(strcmp(cargambr->mbr_partition4.part_type,"e")==0){ext=4;};
                }

                contador++;
                h--;
            }

        }


        fclose(disco);
        int pq =reportedisk1->tam;
        reportedisk *repaux=(reportedisk*)malloc(sizeof(reportedisk));
        repaux=(reportedisk*)malloc(sizeof(reportedisk));
        repaux=reportedisk1->primero;
        while(pq>=1){
            if(repaux->EsMbr==1){

               // printf("\nCREACION FECHA MBR: %s\n",repaux->mbr_fecha_creacion);
            }else
           // printf("\nnombre de la part: %s\n",repaux->part_name);
            repaux=repaux->siguiente;
         pq--;
        }

    /********************FIN DE TRAER EL DISCO COMPLETO Y CARGAR TODAS SUS PARTICIONES ***********************/


/**********************************************************************************************************************************************************************/

   FILE *archivo = fopen("archivosMBR.dot","w");
   if(strcmp(name1,"mbr")==0){
    char *inicio= "digraph{ \n rankdir = LR; \n node [shape = record, color = lightblue]; \n";
    fprintf(archivo, "%s \n", inicio);
   }
    fclose(archivo);
       if(strcmp(name1,"mbr")==0){
            repMBR();
        }
       if(strcmp(name1,"disk")==0){
            repDISK(aux1->path);
        }
    FILE *archivo1 = fopen("archivosMBR.dot","a");

    char *cd = "}";
    fprintf(archivo1,"%s",cd);


    fclose(archivo1);
    char*direccion[200];
    strcpy(direccion,dpth3);
printf("DIRECCIION PATH: %s\n",dpth3);
     /*******************/
         //;
         char ja[50] = "dot -Tjpg archivosMBR.dot -o ";
         strcat(ja,"\"");
         strcat(ja,dpth3);
         strcat(ja,"\"");
         system(ja);

         printf("\nReporte creado con exito.\n");

     /*******************/
         vaciarlistadereportes();
         vaciarlisebr();
         char ja1[100]="firefox ";
         strcat(ja1,"\"");
        strcat(ja1,dpth3);
        strcat(ja1,"\"");
        system(ja1);
     return 0;
}
void repMBR(){

numcirr++;
    char *nombre[200] ;
    strcpy(nombre,"archivosMBR.dot");
    FILE *archivo1 = fopen(nombre, "a");

    char *c1 = "\nsubgraph clusterESTAD";
    fprintf(archivo1, "%s", c1);
    fprintf(archivo1, "%d", numcirr);

    char *c2 = "{ \n label = ""\" Reporte MBR";
    fprintf(archivo1, "%s", c2);

    char *c3 = """\"; \n color=green; \n";
    fprintf(archivo1, "%s", c3);

    if(reportedisk1->tam==0){}
    else{

            char *cc7 = "nodoec1";
            fprintf(archivo1, "%s", cc7);
            int flor=reportedisk1->tam;
            reportedisk* ingresar =(reportedisk*)malloc(sizeof(reportedisk));
            ingresar = reportedisk1->primero;
            char *cq8 = "[label = ""\" ";
            fprintf(archivo1, "%s", cq8);
            while(flor>=1){

           if(ingresar->EsMbr==1){
               fprintf(archivo1, "mbr_disk_Signature: %d",ingresar->mbr_disk_signature);
               char *ccc8 = " | ";
               fprintf(archivo1, "%s", ccc8);
               fprintf(archivo1, "mbr_fecha_creacion: %s",ingresar->mbr_fecha_creacion);
               char *ccc88 = " | ";
               fprintf(archivo1, "%s", ccc88);
               fprintf(archivo1, "mbr_tamanio_disco: %d",ingresar->mbr_tamanio);
               if(reportedisk1->tam==1){ break;}else{
               char *ccc888 = " | ";
                fprintf(archivo1, "%s", ccc888);
               }


           }
           else if(strcmp(ingresar->part_type,"l")==0 ||  strcmp(ingresar->part_type,"1")==0){}
            else{
            fprintf(archivo1, "part_name: %s",ingresar->part_name);
            char *ccc8 = " | ";
            fprintf(archivo1, "%s", ccc8);
            fprintf(archivo1, "part_fit de %s : %s",ingresar->part_name,ingresar->part_fit);
            char *ccc88 = " | ";
            fprintf(archivo1, "%s", ccc88);
            fprintf(archivo1, "part_size de %s: %d",ingresar->part_name,ingresar->part_size);
            char *ccc888 = " | ";
            fprintf(archivo1, "%s", ccc888);
            fprintf(archivo1, "part_start de %s: %d",ingresar->part_name,ingresar->part_start);
            char *ccc8888 = " | ";
            fprintf(archivo1, "%s", ccc8888);
            fprintf(archivo1, "part_status de de %s: %d",ingresar->part_name,ingresar->part_status);
            char *ccc88888 = " | ";
            fprintf(archivo1, "%s", ccc88888);
            fprintf(archivo1, "part_typede de %s: %s",ingresar->part_name,ingresar->part_type);
            char *ccc888888 = " | ";
            fprintf(archivo1, "%s", ccc888888);
            if(flor==1){break;}
            else{
                char *ccc8888888 = " | ";
                fprintf(archivo1, "%s", ccc8888888);
            }

           }

            ingresar=ingresar->siguiente;
            flor--;
            }

            char *cq9 = """\"];\n";
            fprintf(archivo1, "%s", cq9);

        }

        char *c7 = "}\n";
        fprintf(archivo1, "%s", c7);

        if(listalogicas->tam>0){
            /********************************************************************************************************************/
            char *c1 = "\nsubgraph clusterLOGICAS";
            fprintf(archivo1, "%s", c1);
            fprintf(archivo1, "%d", numcirr);

            char *c2 = "{ \n label = ""\" Reporte MBR Particiones Logicas";
            fprintf(archivo1, "%s", c2);

            char *c3 = """\"; \n color=green; \n";
            fprintf(archivo1, "%s", c3);
                    int cuenta =0;
                    int flor=listalogicas->tam;
                    nodolistaebr* auxi =(nodolistaebr*)malloc(sizeof(nodolistaebr));
                    auxi=listalogicas->primero;

                    while(flor>=1){
                        cuenta++;
                        char *cc7 = "nodoec1";
                        fprintf(archivo1, "%s%d", cc7,cuenta);

                        char *cq8 = "[label = ""\"  ";
                        fprintf(archivo1, "%s", cq8);
                       fprintf(archivo1, "part_fit: %s",auxi->part_fit);
                       char *ccc8 = " | ";
                       fprintf(archivo1, "%s", ccc8);
                       fprintf(archivo1, "part_name: %s",auxi->part_name);
                       char *ccc188 = " | ";
                       fprintf(archivo1, "%s", ccc188);
                       fprintf(archivo1, "part_next: %d",auxi->part_next);
                       char *ccc388 = " | ";
                       fprintf(archivo1, "%s", ccc388);
                       fprintf(archivo1, "part_size: %d",auxi->part_size);

                       char *ccc883= " | ";
                       fprintf(archivo1, "%s", ccc883);
                       fprintf(archivo1, "part_start: %d",auxi->part_start);
                       char *ccc8844 = " | ";
                       fprintf(archivo1, "%s", ccc8844);
                       fprintf(archivo1, "part_status: %d",auxi->part_status);

                       char *cq9 = """\"];\n";
                       fprintf(archivo1, "%s", cq9);

                       auxi=auxi->siguiente;
                    flor--;
                    }

                char *c7 = "}\n";
                fprintf(archivo1, "%s", c7);

            /*******************************************************************************************************************/
        }


        fclose(archivo1);

    }
void enviarebrs(char path1[200]){
    mbr *mbr01=(mbr*)malloc(sizeof(mbr));
     FILE *partc =fopen(path1,"r+b");

    fseek(partc,0,SEEK_SET);
    fread(mbr01,sizeof(mbr),1,partc);
    fclose(partc);

    if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
        int inicio =mbr01->mbr_partition1.part_start;

          FILE *archivo=fopen(path1,"rb+");
          fseek(archivo,0,SEEK_SET);
          mbr *aux2 =(mbr *)malloc(sizeof(mbr));
          ebr *aux3=(ebr *)malloc(sizeof(ebr));
          fread(aux2,sizeof(mbr),1,archivo);
          fseek(archivo,inicio,SEEK_CUR);
          fread(aux3,sizeof(ebr),1,archivo);
          int o;
          int bandera=0;

          while(bandera==0){
                    logsumasize=logsumasize+aux3->part_size;
              lisebr(aux3->part_fit,aux3->part_name,aux3->part_next,aux3->part_size,aux3->part_start,aux3->part_status);
            o=aux3->part_size;
            fseek(archivo,o,SEEK_CUR);
             if(aux3->part_next==-1){break;}
             else{
                 fseek(archivo,0,SEEK_CUR);
                 fread(aux3,sizeof(ebr),1,archivo);
             }
          }

          fclose(archivo);

    }
    if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){

        int inicio =mbr01->mbr_partition2.part_start;

          FILE *archivo=fopen(path1,"rb+");
          fseek(archivo,0,SEEK_SET);
          mbr *aux2 =(mbr *)malloc(sizeof(mbr));
          ebr *aux3=(ebr *)malloc(sizeof(ebr));
          fread(aux2,sizeof(mbr),1,archivo);
          fseek(archivo,inicio,SEEK_CUR);
          fread(aux3,sizeof(ebr),1,archivo);
          int o;
          int bandera=0;

          while(bandera==0){
              logsumasize=logsumasize+aux3->part_size;
              lisebr(aux3->part_fit,aux3->part_name,aux3->part_next,aux3->part_size,aux3->part_start,aux3->part_status);

            o=aux3->part_size;
            fseek(archivo,o,SEEK_CUR);
             if(aux3->part_next==-1){break;}
             else{
                 fseek(archivo,0,SEEK_CUR);
                 fread(aux3,sizeof(ebr),1,archivo);
             }
          }

          fclose(archivo);
    }
    if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
        int inicio =mbr01->mbr_partition3.part_start;

          FILE *archivo=fopen(path1,"rb+");
          fseek(archivo,0,SEEK_SET);
          mbr *aux2 =(mbr *)malloc(sizeof(mbr));
          ebr *aux3=(ebr *)malloc(sizeof(ebr));
          fread(aux2,sizeof(mbr),1,archivo);
          fseek(archivo,inicio,SEEK_CUR);
          fread(aux3,sizeof(ebr),1,archivo);
          int o;
          int bandera=0;

          while(bandera==0){
              logsumasize=logsumasize+aux3->part_size;
              lisebr(aux3->part_fit,aux3->part_name,aux3->part_next,aux3->part_size,aux3->part_start,aux3->part_status);

            o=aux3->part_size;
            fseek(archivo,o,SEEK_CUR);
             if(aux3->part_next==-1){break;}
             else{
                 fseek(archivo,0,SEEK_CUR);
                 fread(aux3,sizeof(ebr),1,archivo);
             }
          }

          fclose(archivo);
    }
    if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
        int inicio =mbr01->mbr_partition4.part_start;

          FILE *archivo=fopen(path1,"rb+");
          fseek(archivo,0,SEEK_SET);
          mbr *aux2 =(mbr *)malloc(sizeof(mbr));
          ebr *aux3=(ebr *)malloc(sizeof(ebr));
          fread(aux2,sizeof(mbr),1,archivo);
          fseek(archivo,inicio,SEEK_CUR);
          fread(aux3,sizeof(ebr),1,archivo);
          int o;
          int bandera=0;

          while(bandera==0){
              logsumasize=logsumasize+aux3->part_size;
              lisebr(aux3->part_fit,aux3->part_name,aux3->part_next,aux3->part_size,aux3->part_start,aux3->part_status);

            o=aux3->part_size;
            fseek(archivo,o,SEEK_CUR);
             if(aux3->part_next==-1){break;}
             else{
                 fseek(archivo,0,SEEK_CUR);
                 fread(aux3,sizeof(ebr),1,archivo);
             }
          }

          fclose(archivo);
    }


}
void addlistareportedisk(partition particion){
    reportedisk *aux=(reportedisk*)malloc(sizeof(reportedisk));
    aux->EsMbr=0;
    strcpy(aux->part_fit,particion.part_fit);
    strcpy(aux->part_name,particion.part_name);
    aux->part_size=particion.part_size;
    aux->part_start=particion.part_start;
    aux->part_status=particion.part_status;
    strcpy(aux->part_type,particion.part_type);
    aux->siguiente=NULL;
    aux->anterior=NULL;


    if(reportedisk1->tam==0){
        reportedisk1->primero=reportedisk1->ultimo=aux;
        reportedisk1->tam++;
    }
    else{
        aux->anterior=reportedisk1->ultimo;
       reportedisk1->ultimo->siguiente=aux;
       reportedisk1->ultimo=aux;
       reportedisk1->tam++;
    }

}
void repDISK(char*path1[200]){
    mbr *mbr01=(mbr*)malloc(sizeof(mbr));

     FILE *partc =fopen(path1,"r+b");

    fseek(partc,0,SEEK_SET);
    fread(mbr01,sizeof(mbr),1,partc);
    //printf("\nDENTRO DE --------------------------------------------TYEPE TT%sTT \n",mbr01->mbr_partition1.part_type);
   // printf("\nDENTRO DE --------------------------------------------TYEPE TT%sTT \n",mbr01->mbr_partition2.part_name);
   // printf("\nDENTRO DE --------------------------------------------TYEPE TT%sTT \n",mbr01->mbr_partition3.part_name);

    fclose(partc);
    int part1=mbr01->mbr_partition1.part_start+mbr01->mbr_partition1.part_size;
    int part2=mbr01->mbr_partition2.part_start+mbr01->mbr_partition2.part_size;
    int part3=mbr01->mbr_partition3.part_start+mbr01->mbr_partition3.part_size;
    int part4=mbr01->mbr_partition4.part_start+mbr01->mbr_partition4.part_size;

    int parti1=mbr01->mbr_partition1.part_start;
    int parti2=mbr01->mbr_partition2.part_start;
    int parti3=mbr01->mbr_partition3.part_start;
    int parti4=mbr01->mbr_partition4.part_start;

    int size1=mbr01->mbr_partition1.part_size;
    int size2=mbr01->mbr_partition2.part_size;
    int size3=mbr01->mbr_partition3.part_size;
    int size4=mbr01->mbr_partition4.part_size;
    /************************************************/
    numcirr++;
        char *nombre[200] ;
        strcpy(nombre,"archivosMBR.dot");
        FILE *archivo1 = fopen(nombre, "a");

        char *c1 = "digraph html { abc [shape=none, margin=0,shape = record, color = lightblue, label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" \n CELLPADDING=\"4\">\n <TR> \n <TD ROWSPAN=\"3\"><FONT COLOR=\"green\">MBR</FONT><BR/></TD> ";

        fprintf(archivo1, "%s", c1);


    //para uno menor
    if((parti1<parti2 || size2<1) && (parti1<parti3|| size3<1) && (parti1<parti4|| size4<1) && mbr01->mbr_partition1.part_size>0){
      /// printf("\nDENTRO DE IF UNO MENOR\n");

        if(parti1==0){


            if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
          //  printf("\nDENTRO DE --------------------------------------------PRI UNO\n");
            char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", l1);
            }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", l1);
            }
        }else{
            char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
            fprintf(archivo1, "%s", l1);
            if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
            char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", l1);
            }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", l1);
            }

        }

        if(size2<1 && size3<1 && size4<1 && part1<mbr01->mbr_tamanio){
            char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
            fprintf(archivo1, "%s", l1);
        }
        //particion 2 menor
        if((parti2<parti4|| size4<1) &&(parti2<parti3|| size3<1) && mbr01->mbr_partition2.part_size>0)
        {
       // printf("\nDENTRO DE --------------------------------------------\n");
            int j= part1-parti2;
            if(j==0){
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
             //   printf("\nDENTRO DE --------------------------------------------PRI DOS\n");
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }else{
                char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", l1);
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }

            }
            if(size3<1 && size4<1 && part2<mbr01->mbr_tamanio){
                char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", l1);
            }
            //particion 3 menor
            if((parti3<parti4 || size4<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size4<1 && part3<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }
            //particion4 menor
            if((parti4<parti3 || size3<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size3<1 && part4<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);

                }
            }

        }


        /**********************************************************************************************************************/
        //particion 3 menor
        if((parti3<parti4|| size4<1) &&(parti3<parti2|| size2<1) && mbr01->mbr_partition3.part_size>0){
            int j= part1-parti3;
            if(j==0){
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }else{
                char *l1="<TD RO3SPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", l1);
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }

            }
            if(size2<1 && size4<1 && part3<mbr01->mbr_tamanio){
                char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", l1);
            }
            //particion 2 menor
            if((parti2<parti4 || size4<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size4<1 && part2<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                     else if(part2<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }
            //particion4 menor
            if((parti4<parti2 || size2<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size2<1 && part4<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);

                }
            }

        }
        /**********************************************************************************************************************/


        /***********************************************************************************************************/
        //particion 4 menor
        if((parti4<parti2|| size2<1) &&(parti4<parti3|| size3<1) && mbr01->mbr_partition4.part_size>0){
            int j= part1-parti4;
            if(j==0){
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }else{
                char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", l1);
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", l1);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", l1);
                }

            }
            if(size3<1 && size2<1 && part4<mbr01->mbr_tamanio){
                char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", l1);
            }
            //particion 3 menor
            if((parti3<parti2 || size2<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size2<1 && part3<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }
            }
            //particion2 menor
            if((parti2<parti3 || size3<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }else{
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", l1);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", l1);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", l1);
                    }

                }
                if(size3<1 && part2<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }
                    }else{
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", l1);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *l1="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", l1);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *l1="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", l1);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", l1);
                    }
                }
                    else if( part2<mbr01->mbr_tamanio){
                    char *l1="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", l1);

                }
            }

        }

        /***********************************************************************************************************/


    }



//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

    //para dos menor
    if((parti2<parti1 || size1<1) && (parti2<parti3|| size3<1) && (parti2<parti4|| size4<1) && mbr01->mbr_partition2.part_size>0){
       // printf("\nDENTRO DE IF\n");
        if(parti2==0){
            if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }
        }else{
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
            fprintf(archivo1, "%s", lq);
            if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }

        }

        if(size1<1 && size3<1 && size4<1 && part2<mbr01->mbr_tamanio){
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
            fprintf(archivo1, "%s", lq);
        }
        //particion 1 menor
        if((parti1<parti4|| size4<1) &&(parti1<parti3|| size3<1) && mbr01->mbr_partition1.part_size>0){
            int j= part2-parti1;
            if(j==0){
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size3<1 && size4<1 && part1<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 3 menor
            if((parti3<parti4 || size4<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size4<1 && part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion4 menor
            if((parti4<parti3 || size3<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size3<1 && part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }


        /**********************************************************************************************************************/
        //particion 3 menor
        if((parti3<parti4|| size4<1) &&(parti3<parti1|| size1<1) && mbr01->mbr_partition3.part_size>0){
            int j= part2-parti3;
            if(j==0){
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD RO3SPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size1<1 && size4<1 && part3<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 1 menor
            if((parti1<parti4 || size4<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size4<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion4 menor
            if((parti4<parti1 || size1<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }
        /**********************************************************************************************************************/


        /***********************************************************************************************************/
        //particion 4 menor
        if((parti4<parti1|| size1<1) &&(parti4<parti3|| size3<1) && mbr01->mbr_partition4.part_size>0){
            int j= part2-parti4;
            if(j==0){
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size3<1 && size1<1 && part4<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 3 menor
            if((parti3<parti1 || size1<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion1 menor
            if((parti1<parti3 || size3<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size3<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }

        /***********************************************************************************************************/


    }

   //para tres menor
    if((parti3<parti1 || size1<1) && (parti3<parti2|| size2<1) && (parti3<parti4|| size4<1) && mbr01->mbr_partition3.part_size>0){
       // printf("\nDENTRO DE IF\n");
        if(parti3==0){
            if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }
        }else{
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
            fprintf(archivo1, "%s", lq);
            if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }

        }

        if(size1<1 && size2<1 && size4<1 && part3<mbr01->mbr_tamanio){
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
            fprintf(archivo1, "%s", lq);
        }
        //particion 1 menor
        if((parti1<parti4|| size4<1) &&(parti1<parti2|| size2<1) && mbr01->mbr_partition1.part_size>0){
            int j= part3-parti1;
            if(j==0){
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else{
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size2<1 && size4<1 && part1<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 2 menor
            if((parti2<parti4 || size4<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size4<1 && part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion4 menor
            if((parti4<parti2 || size2<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size2<1 && part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }


        /**********************************************************************************************************************/
        //particion 2 menor
        if((parti2<parti4|| size4<1) &&(parti2<parti1|| size1<1) && mbr01->mbr_partition2.part_size>0){
            int j= part3-parti2;
            if(j==0){
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD RO2SPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size1<1 && size4<1 && part2<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 1 menor
            if((parti1<parti4 || size4<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size4<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition4.part_size>0){
                    int j= parti4-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part4<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion4 menor
            if((parti4<parti1 || size1<1) && mbr01->mbr_partition4.part_size>0){
                int j= parti4-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part4;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part4<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }
        /**********************************************************************************************************************/


        /***********************************************************************************************************/
        //particion 4 menor
        if((parti4<parti1|| size1<1) &&(parti4<parti2|| size2<1) && mbr01->mbr_partition4.part_size>0){
            int j= part3-parti4;
            if(j==0){
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size2<1 && size1<1 && part4<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 2 menor
            if((parti2<parti1 || size1<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion1 menor
            if((parti1<parti2 || size2<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part4;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size2<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }

        /***********************************************************************************************************/


    }

  //para cuatro menor
    if((parti4<parti1 || size1<1) && (parti4<parti3|| size3<1) && (parti4<parti2|| size2<1) && mbr01->mbr_partition4.part_size>0){
        //printf("\nDENTRO DE IF\n");
        if(parti4==0){
            if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }
        }else{
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
            fprintf(archivo1, "%s", lq);
            if(strcmp(mbr01->mbr_partition4.part_type,"p")==0){
            char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
            fprintf(archivo1, "%s", lq);
            }else if(strcmp(mbr01->mbr_partition4.part_type,"e")==0){
                char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                fprintf(archivo1, "%s", lq);
            }

        }

        if(size1<1 && size3<1 && size2<1 && part4<mbr01->mbr_tamanio){
            char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
            fprintf(archivo1, "%s", lq);
        }
        //particion 1 menor
        if((parti1<parti2|| size2<1) &&(parti1<parti3|| size3<1) && mbr01->mbr_partition1.part_size>0){
            int j= part4-parti1;
            if(j==0){
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size3<1 && size2<1 && part1<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 3 menor
            if((parti3<parti2 || size2<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size2<1 && part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion2 menor
            if((parti2<parti3 || size3<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part1;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size3<1 && part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }


        /**********************************************************************************************************************/
        //particion 3 menor
        if((parti3<parti2|| size2<1) &&(parti3<parti1|| size1<1) && mbr01->mbr_partition3.part_size>0){
            int j= part4-parti3;
            if(j==0){
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD RO3SPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size1<1 && size2<1 && part3<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 1 menor
            if((parti1<parti2 || size2<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size2<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition2.part_size>0){
                    int j= parti2-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part2<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion2 menor
            if((parti2<parti1 || size1<1) && mbr01->mbr_partition2.part_size>0){
                int j= parti2-part3;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part2;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part2<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }
        /**********************************************************************************************************************/


        /***********************************************************************************************************/
        //particion 2 menor
        if((parti2<parti1|| size1<1) &&(parti2<parti3|| size3<1) && mbr01->mbr_partition2.part_size>0){
            int j= part4-parti2;
            if(j==0){
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }else{
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                fprintf(archivo1, "%s", lq);
                if(strcmp(mbr01->mbr_partition2.part_type,"p")==0){
                char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                fprintf(archivo1, "%s", lq);
                }else if(strcmp(mbr01->mbr_partition2.part_type,"e")==0){
                    char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                    fprintf(archivo1, "%s", lq);
                }

            }
            if(size3<1 && size1<1 && part2<mbr01->mbr_tamanio){
                char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                fprintf(archivo1, "%s", lq);
            }
            //particion 3 menor
            if((parti3<parti1 || size1<1) && mbr01->mbr_partition3.part_size>0){
                int j= parti3-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size1<1 && part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition1.part_size>0){
                    int j= parti1-part3;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part1<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                     else if(part3<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }
            }
            //particion1 menor
            if((parti1<parti3 || size3<1) && mbr01->mbr_partition1.part_size>0){
                int j= parti1-part2;
                if(j==0){
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }else{
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                    fprintf(archivo1, "%s", lq);
                    if(strcmp(mbr01->mbr_partition1.part_type,"p")==0){
                    char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                    fprintf(archivo1, "%s", lq);
                    }else if(strcmp(mbr01->mbr_partition1.part_type,"e")==0){
                        char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                        fprintf(archivo1, "%s", lq);
                    }

                }
                if(size3<1 && part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);
                }    else  if(mbr01->mbr_partition3.part_size>0){
                    int j= parti3-part1;
                    if(j==0){
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }
                    }else{
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD >\n";
                        fprintf(archivo1, "%s", lq);
                        if(strcmp(mbr01->mbr_partition3.part_type,"p")==0){
                        char *lq="<TD ROWSPAN=\"3\">PRIMARIA</TD>";
                        fprintf(archivo1, "%s", lq);
                        }else if(strcmp(mbr01->mbr_partition3.part_type,"e")==0){
                            char *lq="<TD COLSPAN=\"50\">EXTENDIDA</TD>";
                            fprintf(archivo1, "%s", lq);
                        }

                    }

                    if(part3<mbr01->mbr_tamanio){
                        char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                        fprintf(archivo1, "%s", lq);
                    }
                }
                    else if( part1<mbr01->mbr_tamanio){
                    char *lq="<TD ROWSPAN=\"3\">LIBRE</TD>";
                    fprintf(archivo1, "%s", lq);

                }
            }

        }

        /***********************************************************************************************************/


    }



        if(listalogicas->tam>0){
            char *cq9 = "</TR><TR>";
            fprintf(archivo1, "%s", cq9);
            int aa =listalogicas->tam;

            while(aa>=1){

                char *cq9 = "<TD>EBR</TD><TD>Logica</TD>";
                fprintf(archivo1, "%s", cq9);
                aa--;
            }




        }

    char *cq9 = "</TR></TABLE>>];\n";
    fprintf(archivo1, "%s", cq9);
    fclose(archivo1);




}
void vaciarlistadereportes(){
    reportedisk1->primero=NULL;
    reportedisk1->ultimo=NULL;
    reportedisk1->tam=0;
}
void vaciarlisebr(){
    listalogicas->primero=NULL;
    listalogicas->ultimo=NULL;
    listalogicas->tam=0;
}
void lisebr(char*fit[10],char*name[30],int next,int size, int start, int status){
    nodolistaebr*nuevo =(nodolistaebr*)malloc(sizeof(nodolistaebr));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    strcpy(nuevo->part_fit,fit);
    strcpy(nuevo->part_name,name);
    nuevo->part_next=next;
    nuevo->part_size=size;
    nuevo->part_start=start;
    nuevo->part_status=status;
    if(listalogicas->tam==0){
        listalogicas->primero=listalogicas->ultimo=nuevo;
        listalogicas->tam++;
    }else{
        nuevo->anterior=listalogicas->ultimo;
        listalogicas->ultimo->siguiente=nuevo;
        listalogicas->ultimo=nuevo;
        listalogicas->tam++;
    }


}
//FIN METODOS FASE 12































