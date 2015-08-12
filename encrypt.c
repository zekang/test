
/************************************************************************/
/* 文件加密/解密操作                                                    */
/************************************************************************/
static int encrypt(const char *src, const char * dest, const char *key)
{
	int keylen = strlen(key);
	char *buffer = (char *) malloc(keylen + 1);
	int readlen = 0;
	FILE *fpwrite, *fpread;
	if (buffer == NULL){
		printf("malloc failure\n");
		return FAILURE;
	}
	buffer = (char *)malloc(keylen + 1);
	if (buffer == NULL){
		printf("malloc failure\n");
		return FAILURE;
	}
	fpread = fopen(src, "rb");
	if (!fpread){
		printf("%s file open failure\n", src);
		return FAILURE;
	}

	fpwrite = fopen(dest, "wb");
	if (!fpwrite){
		if (fpread){
			fclose(fpread);
		}
		printf("%s file open failure\n", dest);
		return FAILURE;
	}
	while (!feof(fpread)){
		readlen = fread(buffer, 1, keylen, fpread);
		for (int i = 0; i < readlen; i++){
			fputc(buffer[i] ^ key[i], fpwrite);
		}
	}
	fclose(fpread);
	fclose(fpwrite);
	free(buffer);
	return SUCCESS;
}


void main()
{
	char *key = "123456";
	char *file = "d:/c/li_default.html";
	char *outfile = "d:/c/li_default.html.bak";
	int result = encrypt(file, outfile, key);
	printf("\n%d\n", result);
	getchar();
}
