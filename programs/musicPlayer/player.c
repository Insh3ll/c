#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

//定义wav文件头结构
struct WAV_HEADER
{
	char rld[4];//fiff标志符号
	int rLen;//文件大小
	char wld[4];//格式类型
	char fld[4];
	int fLen;//sizeof(wave format matex)
	short formatTag;//编码格式
	short channels;//声道数
	int nSamplePersec;//采样频率
	int nAvgBitsPerSample;
	short wBlockAlign;//块对齐
	short wBitsPerSample;//采样的位数
	char dld[4];
	int sampleLength;//音频数据大小
}wav_header;

int set_pcm_player(FILE *fp);

//主函数
int main(int argc,char *argv[])
{
	if(argc!=2)
	{	
		printf("Usage:palyer+example.wav\n");
		exit(1);
	}
	
	int nread;
	FILE *fp;
	fp=fopen(argv[1],"rb");
	if(fp==NULL)
	{
		perror("open file failed\n");
		exit(1);
	}

	nread=fread(&wav_header,sizeof(wav_header),1,fp);
	printf("nread=%d\n",nread);

	printf("文件大小rlen:%d\n",wav_header.rLen);
	printf("声道数：%d\n",wav_header.channels);
	printf("采样频率：%d\n",wav_header.nSamplePersec);
	printf("采样的位数：%d\n",wav_header.wBitsPerSample);
	
	printf("文件大小sampleLength=%d\n",wav_header.sampleLength);

	while(1)
		set_pcm_play(fp);
	fclose(fp);	
	return 0;
}

//播放函数
int set_pcm_play(FILE *fp)
{
	int rc;
	int ret;
	int size;	

	snd_pcm_t* handle;//PCI设备句柄
	snd_pcm_hw_params_t* params;//硬件信息和PCM流配置
	unsigned int val;
	int dir=0;
	snd_pcm_uframes_t frames;
	char *buffer;
	int channels=wav_header.channels;
	int frequency=wav_header.nSamplePersec;
	int bit=wav_header.wBitsPerSample;
	int datablock=wav_header.wBlockAlign;
	unsigned char ch[100];//存储wav文件的头信息

	rc=snd_pcm_open(&handle,"default",SND_PCM_STREAM_PLAYBACK,0);
	if(rc<0)
	{
		perror("open PCM device failed\n");
		exit(1);
	}

	snd_pcm_hw_params_alloca(&params);//分配params结构体
	if(rc<0)
	{
		perror("snd_pcm_hw_params_alloca\n");
		exit(1);
	}
	
	rc=snd_pcm_hw_params_any(handle,params);//初始化params
	if(rc<0)
	{
		perror("snd_pcm_hw_params_any");
		exit(1);
	}

	rc=snd_pcm_hw_params_set_access(handle,params,SND_PCM_ACCESS_RW_INTERLEAVED);//初始化访问权限
	if(rc<0)
	{
		perror("set_pcm_hw_set_access");
		exit(1);
	}

	//采样位数
	switch(bit/8)
	{
		case 1:snd_pcm_hw_params_set_format(handle,params,SND_PCM_FORMAT_U8);break;
		case 2:snd_pcm_hw_params_set_format(handle,params,SND_PCM_FORMAT_S16_LE);break;
		case 3:snd_pcm_hw_params_set_format(handle,params,SND_PCM_FORMAT_S24_LE);break;
	}

	rc=snd_pcm_hw_params_set_channels(handle,params,channels);//设置声道
	if(rc<0)
	{
		perror("snd_pcm_hw_params_set_channel\n");
		exit(1);
	}

	val=frequency;
	rc=snd_pcm_hw_params_set_rate_near(handle,params,&val,&dir);//设置频率
	if(rc<0)
	{
		perror("snd_pcm_hw_params_set_rate_near\n");
		exit(1);
	}
	
	rc=snd_pcm_hw_params(handle,params);
	if(rc<0)
	{
		perror("snd_pcm_hw_params\n");
		exit(1);
	}

	rc=snd_pcm_hw_params_get_period_size(params,&frames,&dir);//获取周期长度
	if(rc<0)
	{
		perror("snd_pcm_hw_params_get_period_size\n");
		exit(1);
	}

	size=frames*datablock;//代表数据块长度

	buffer=(char*)malloc(size);
	fseek(fp,58,SEEK_SET);//定位歌曲到数据区

	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		ret=fread(buffer,size,1,fp);
		if(ret==0)
		{
			printf("歌曲写入结束\n");
			break;
		}
		//写音频数据到PCM设备
		while(ret=snd_pcm_writei(handle,buffer,frames)<0)
		{
			usleep(2000);
			if(ret==-EPIPE)//EPIPE means underrun
			{
				fprintf(stderr,"underrun occurred\n");
				//完成硬件参数设置，使设备准备好
				snd_pcm_prepare(handle);
			}
			else if(ret<0)
			{
				fprintf(stderr,"error form writei:%s\n",snd_strerror(ret));
			}
		}
	}

	snd_pcm_drain(handle);
	snd_pcm_close(handle);
	free(buffer);
	return 0;
}









