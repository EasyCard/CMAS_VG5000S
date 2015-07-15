

#include "ECCAPP.h"

USHORT ECC_CheckXML(STR * File)
{
        ezxml_t  xml =ezxml_parse_file(File);
        if(xml==NULL){
           
            return FALSE;
        }
        ezxml_free(xml);
        return TRUE;     
}
USHORT ECC_ADDXMLNODE(ezxml_t  DestXml,BYTE * TAG,BYTE * NAME, BYTE * Data)
{   
      ezxml_t node=ezxml_add_child_d(DestXml,TAG,0);
      if(NAME !=NULL)ezxml_set_attr_d(node,"name",NAME);
      
      ezxml_set_txt_d(node,Data); 
      return d_OK;
}


USHORT ECC_GetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT)
{
    
    STR  msgstr[64];
    USHORT ret=d_OK;
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, NodeName,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",NodeName,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret= d_ERR_XMLError;
        goto exit;
    }
    if(strlen(ConfigNode->txt)==0) {
     
      ret= d_Fail;
      goto exit;
    }
      sprintf(TEXT,"%s",ConfigNode->txt);
exit:
    ezxml_free(configfile);
 
    return ret;
}
USHORT ECC_GetXMLTag2(STR * FILE, STR * Node1Name, STR * Node2Name,STR *ItemName, STR * TEXT)
{
    USHORT ret=0;
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret= d_ERR_XMLError;
        goto exit;
    }
    if(strlen(ConfigNode->txt)==0) {
     
      ret= d_Fail;
      goto exit;
    }
      sprintf(TEXT,"%s",ConfigNode->txt);
exit:
    ezxml_free(configfile);
    return ret;
}
USHORT ECC_GetXMLTag3(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR *ItemName, STR * TEXT)
{
    USHORT ret=0;
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,Node3Name,0,ItemName,-1);
     if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret= d_ERR_XMLError;
        goto exit;
    }
    if(strlen(ConfigNode->txt)==0) {
     
      ret= d_Fail;
      goto exit;
    }
      sprintf(TEXT,"%s",ConfigNode->txt);
exit:
    ezxml_free(configfile);
    return ret;
}
USHORT ECC_GetXMLTag4(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR * Node4Name,STR *ItemName, STR * TEXT)
{
       USHORT ret=0;
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,Node3Name,0,Node4Name,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret= d_ERR_XMLError;
        goto exit;
    }
    if(strlen(ConfigNode->txt)==0) {
     
      ret= d_Fail;
      goto exit;
    }
      sprintf(TEXT,"%s",ConfigNode->txt);
exit:
    ezxml_free(configfile);
    return ret;
}

USHORT ECC_SetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT)
{ 
    USHORT ret=0;
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, NodeName,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",NodeName,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret=d_ERR_XMLError;
        goto exit;
    }
  
    ConfigNode= ezxml_set_txt(ConfigNode,TEXT);
    ret=ECC_WriteXMLFILE(FILE,configfile);
    if(ret!=d_OK) { 
        ret=d_ERR_XMLError;
        goto exit;
    }
  exit:
    ezxml_free(configfile);
    return ret;
}
USHORT ECC_SetXMLTag2(STR * FILE, STR * Node1Name, STR * Node2Name,STR *ItemName, STR * TEXT)
{
     USHORT ret=0;
   
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        STR  msgstr[64];
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret=d_ERR_XMLError;
        goto exit;
    }
    
     ConfigNode= ezxml_set_txt(ConfigNode,TEXT);
     ret=ECC_WriteXMLFILE(FILE,configfile);
    if(ret!=d_OK) { 
        ret=d_ERR_XMLError;
        goto exit;
    }
 exit :   
    ezxml_free(configfile);
    return 0;
}
USHORT ECC_SetXMLTag3(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR *ItemName, STR * TEXT)
{
    USHORT ret;
  
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,Node3Name,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret=d_ERR_XMLError;
        goto exit;
    }
     ConfigNode= ezxml_set_txt(ConfigNode,TEXT);
     ret=ECC_WriteXMLFILE(FILE,configfile);
    if(ret!=d_OK) {
      ret=d_ERR_XMLError;
        goto exit;
    }
    
exit :    
   
    ezxml_free(configfile);
     
    return 0;
}
USHORT ECC_SetXMLTag4(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR * Node4Name,STR *ItemName, STR * TEXT)
{
    USHORT ret;
    STR  msgstr[64];
    ezxml_t configfile = ezxml_parse_file(FILE);
    ezxml_t ConfigNode= ezxml_get(configfile, Node1Name,0,Node2Name,0,Node3Name,0,Node4Name,0,ItemName,-1);
    if(ConfigNode ==NULL){ 
        sprintf(msgstr,"Get XML %s %s Tag Fail",Node1Name,ItemName);
        SystemLog("ECC_GetXMLTag",msgstr);
        ret=d_ERR_XMLError;
        goto exit;
    }
    ConfigNode= ezxml_set_txt(ConfigNode,TEXT);
     ret=ECC_WriteXMLFILE(FILE,configfile);
    if(ret!=d_OK) {
      ret=d_ERR_XMLError;
        goto exit;
    }
exit :    
    ezxml_free(configfile);
return ret;
}
//type = fopen type
/*                       表 文件操作类型
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
          字符                含义
    ────────────────────────────
           "r"           打开文字文件只读
           "w"           创建文字文件只写
           "a"           增补, 如果文件不存在则创建一个
           "r+"          打开一个文字文件读/写
           "w+"          创建一个文字文件读/写
           "a+"          打开或创建一个文件增补
           "b"           二进制文件(可以和上面每一项合用)
           "t"           文这文件(默认项)
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
   　文件使用方式 　　　　　　　意 义
“rt”　　　　　　只读打开一个文本文件，只允许读数据 
“wt”　　　　　　只写打开或建立一个文本文件，只允许写数据
“at”　　　　　　追加打开一个文本文件，并在文件末尾写数据
“rb”　　　　　　只读打开一个二进制文件，只允许读数据
“wb”　　　　 　 只写打开或建立一个二进制文件，只允许写数据
“ab” 　　　　 　追加打开一个二进制文件，并在文件末尾写数据
“rt+”　　　　　 读写打开一个文本文件，允许读和写
“wt+”　　　　　 读写打开或建立一个文本文件，允许读写
“at+”　　　　　 读写打开一个文本文件，允许读，或在文件末追加数 据
“rb+”　　　　　 读写打开一个二进制文件，允许读和写 
“wb+”　　　　　 读写打开或建立一个二进制文件，允许读和写
“ab+” 　　　　　读写打开一个二进制文件，允许读，或在文件末追加数据*/
USHORT ECC_WriteXMLFILE(STR * FileName,ezxml_t xml)
{
     char *DATA;
      
     STR tmpfile[7+1]="tmpfile";
     if( remove( tmpfile) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove tmpfile Fail. ");
     DATA=ezxml_toxml(xml);
     FILE * fd ;	 
     fd = fopen(tmpfile, "w+");
     if(fd==NULL){
          SystemLog("ECC_WriteXMLFILE","Temp File OPEN Fail. ");
         return d_Fail;
     }
    fseek(fd,0,SEEK_SET);
    fprintf(fd,"%s",DATA);
    //2014.11.21, kobe added it, 
    //fflush and fsync, could be sure that data in temp Buffer be written in file immediately
    fflush(fd);
    fsync(fileno(fd));
    //end
    
    fclose(fd);
  
    if( remove( FileName) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove File Fail. ");
   
    if(rename(tmpfile,FileName) != 0 )
         SystemLog("ECC_WriteXMLFILE","rename File Fail. ");
    free(DATA);
    
    return d_OK;
}
USHORT ECC_WriteXMLFILE2(STR * FileName,ezxml_t xml,STR *TagName)
{
     char *DATA;
     
     STR tmpfile[7+1]="tmpfile";
     if( remove( tmpfile) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove tmpfile Fail. ");
     DATA=ezxml_toxml(xml);
     FILE * fd ;	 
     fd = fopen(tmpfile, "w+");
     if(fd==NULL){
          SystemLog("ECC_WriteXMLFILE","Temp File OPEN Fail. ");
         return d_Fail;
     }
    fprintf(fd,"<%s>\n",TagName);
     
   // fseek(fd,0,SEEK_SET);
    fprintf(fd,"%s",DATA);
    fprintf(fd,"<%s>\n",TagName);
    //2014.11.21, kobe added it, 
    //fflush and fsync, could be sure that data in temp Buffer be written in file immediately
    fflush(fd);
    fsync(fileno(fd));
    //end
    
    fclose(fd);
  
    if( remove( FileName) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove File Fail. ");
   
    if(rename(tmpfile,FileName) != 0 )
         SystemLog("ECC_WriteXMLFILE","rename File Fail. ");
    free(DATA);      
    return d_OK;
}
/*
USHORT LoadXMLFile2(ezxml_t* xml, STR * filename)
{
    char * errstr;      
    xml = ezxml_parse_file((const char *)filename);
    if(xml ==NULL){
        SystemLog("LoadXMLFile","ezxml_parse_file FAIL. ");
       return d_Fail;
    }
   
    return d_OK;
}*/
ezxml_t LoadXMLFile( STR * filename)
{
  
    ezxml_t xml = ezxml_parse_file(filename);
    if(xml ==NULL){
        SystemLog("LoadXMLFile","ezxml_parse_file FAIL. ");
       return NULL;
    }
   
    return xml;
}
USHORT ECC_WriteXmlHeader(STR * TagName,STR * filename)
{
    FILE * fd = fopen(filename, "ab");
     if(fd==NULL){
          SystemLog("ECC_WriteXmlHeader"," File OPEN Fail. ");
         return d_Fail;
     }
   
    fprintf(fd,"<%s>\n",TagName);
    fclose(fd);
    return  d_OK; 
}
USHORT ECC_WriteXmlEND(STR * TagName,STR * filename)
{
    FILE * fd = fopen(filename, "ab");
     if(fd==NULL){
          SystemLog("ECC_WriteXmlEND"," File OPEN Fail. ");
         return d_Fail;
     }
   
    fprintf(fd,"\n</%s>",TagName);
    fclose(fd);
    return  d_OK; 
}

USHORT ECC_RemoveXmlEND(STR * TagName,STR * filename)
{
    FILE * fd = fopen(filename, "w+");
    BYTE *buf;
    BYTE str[20+1];
    memset(str,0x00,sizeof(str));
     if(fd==NULL){
          SystemLog("ECC_WriteXmlEND"," File OPEN Fail. ");
         return 0;
     }
   
    sprintf(str,"</%s>",TagName);
    fseek(fd, strlen(str), SEEK_END);   
    long FileEND = ftell(fd);
   
    fseek(fd, 0, SEEK_SET);
    buf =malloc(FileEND);
    long Size=fread((BYTE *)buf,FileEND,1, fd);
     fclose(fd);
    
     STR tmpfile[7+1]="tmpfile";
     if( remove( tmpfile) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove tmpfile Fail. ");
 
      FILE * Tmpfd ;	 
     Tmpfd = fopen(tmpfile, "w");
     if(Tmpfd==NULL){
          SystemLog("ECC_WriteXMLFILE","Temp File OPEN Fail. ");
         return d_Fail;
     }
    fseek(Tmpfd,0,SEEK_SET);
     fwrite((UCHAR *)&buf,Size,1,Tmpfd);
    fclose(Tmpfd);
  
    if( remove( filename) != 0 )
          SystemLog("ECC_WriteXMLFILE","remove File Fail. ");
   
    if(rename(tmpfile,filename) != 0 )
         SystemLog("ECC_WriteXMLFILE","rename File Fail. ");
    return  d_OK; 
}