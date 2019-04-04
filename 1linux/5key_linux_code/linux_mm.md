# 共享内存 #

**mmap()及其相关系统调用**

------

    #include <sys/mman.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    typedef struct{
      char name[4];
      int  age;
    }people;
    main(int argc, char** argv) // map a normal file as shared mem:
    {
      int fd,i;
      people *p_map;
      char temp;
       
      fd=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,00777);
      lseek(fd,sizeof(people)*5-1,SEEK_SET);
      write(fd,"",1);
       
      p_map = (people*) mmap( NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,
            MAP_SHARED,fd,0 );
      close( fd );
      temp = 'a';
      for(i=0; i<10; i++)
      {
        temp += 1;
        memcpy( ( *(p_map+i) ).name, &temp,2 );
        ( *(p_map+i) ).age = 20+i;
      }
      printf(" initialize over \n ")；
      sleep(10);
      munmap( p_map, sizeof(people)*10 );
      printf( "umap ok \n" );
    }
    /*-------------map_normalfile2.c-----------*/
    #include <sys/mman.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    typedef struct{
      char name[4];
      int  age;
    }people;
    main(int argc, char** argv)  // map a normal file as shared mem:
    {
      int fd,i;
      people *p_map;
      fd=open( argv[1],O_CREAT|O_RDWR,00777 );
      p_map = (people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,
           MAP_SHARED,fd,0);
      for(i = 0;i<10;i++)
      {
      printf( "name: %s age %d;\n",(*(p_map+i)).name, (*(p_map+i)).age );
      }
      munmap( p_map,sizeof(people)*10 );
    }


**系统V共享内存原理**

