#include "Book.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <cstdio>
/*
 * Class:     Book
 * Method:    getSymbolBook
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Book_getSymbolBook
  (JNIEnv *env, jobject o) {
  		char *str = (char *) malloc(10*sizeof(char));
  		jstring jstr;
  		
  		int shmid = shmget(1234, 10*sizeof(char), 0666 | IPC_CREAT);
		const void *shm = shmat(shmid, NULL, 0);
		if(shm == (const void *) -1)
			perror("shmat");
			
		for(int i=0, char *s = (char *)shm; *s!='*' && i<10; i++, s++) {
			str[i] = *s;
		}
		
		jstr = (*env)->NewStringUTF(env, str);
		free(str);
		
		shmdt(shm_data);
		shmctl(shmid, IPC_RMID, NULL);
		
		return jstr;	
  }

/*
 * Class:     Book
 * Method:    getBidValueBook
 * Signature: ()[F
 */
JNIEXPORT jfloatArray JNICALL Java_Book_getBidValueBook
  (JNIEnv *, jobject) {
  		jfloatArray jfa = (*env)->NewIntArray(env, 10);
  		jfloat fa[10];
  		int shmid = shmget(2345, 10*sizeof(float), 0666 | IPC_CREAT);
		const void *shm = shmat(shmid, NULL, 0);
		if(shm == (const void *) -1)
			perror("shmat");
		
		for(float *s = shm, int i=0; i<10; i++, s++)
			fa[i] = *s;
		
		shmdt(shm_data);
		shmctl(shmid, IPC_RMID, NULL);
		(*env)->SetFloatArrayRegion(env, jfa, 0, 10, fa);
		
		return jfa;	
  }

/*
 * Class:     Book
 * Method:    getBidSizeBook
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_Book_getBidSizeBook
  (JNIEnv *, jobject) {
  		jintArray jia = (*env)->NewIntArray(env, 10);
  		jint ia[10];
  		int shmid = shmget(3456, 10*sizeof(int), 0666 | IPC_CREAT);
		const void *shm = shmat(shmid, NULL, 0);
		if(shm == (const void *) -1)
			perror("shmat");
		
		for(int *s = shm, int i=0; i<10; i++, s++)
			ia[i] = *s;
		
		shmdt(shm_data);
		shmctl(shmid, IPC_RMID, NULL);
		(*env)->SetIntArrayRegion(env, jia, 0, 10, ia);
		
		return jia;
  }

/*
 * Class:     Book
 * Method:    getOfferValueBook
 * Signature: ()[F
 */
JNIEXPORT jfloatArray JNICALL Java_Book_getOfferValueBook
  (JNIEnv *, jobject) {
  		jfloatArray jfa = (*env)->NewIntArray(env, 10);
  		jfloat fa[10];
  		int shmid = shmget(2345, 10*sizeof(float), 0666 | IPC_CREAT);
		const void *shm = shmat(shmid, NULL, 0);
		if(shm == (const void *) -1)
			perror("shmat");
		
		for(float *s = shm, int i=0; i<10; i++, s++)
			fa[i] = *s;
		
		shmdt(shm_data);
		shmctl(shmid, IPC_RMID, NULL);
		(*env)->SetFloatArrayRegion(env, jfa, 0, 10, fa);
		
		return jfa;	
  }

/*
 * Class:     Book
 * Method:    getOfferSizeBook
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_Book_getOfferSizeBook
  (JNIEnv *, jobject) {
  		jintArray jia = (*env)->NewIntArray(env, 10);
  		jint ia[10];
  		int shmid = shmget(3456, 10*sizeof(int), 0666 | IPC_CREAT);
		const void *shm = shmat(shmid, NULL, 0);
		if(shm == (const void *) -1)
			perror("shmat");
		
		for(int *s = shm, int i=0; i<10; i++, s++)
			ia[i] = *s;
		
		shmdt(shm_data);
		shmctl(shmid, IPC_RMID, NULL);
		(*env)->SetIntArrayRegion(env, jia, 0, 10, ia);
		
		return jia;
  }
