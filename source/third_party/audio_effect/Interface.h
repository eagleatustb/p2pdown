#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <windows.h>

// Surround�ӿ�
class ISurround
{
public:
	// ���û���ǿ��(0~1.0)
	virtual void SetSurround(float fValue) = 0;

public:
	// ���ò�����
	virtual void SetSamplingRate(int nSamplingRate) = 0;

	// ������������
	virtual void SetChannels(int nChannels) = 0;

	// ��λЧ������������Seek���л�����ʱ����
	virtual void Reset() = 0;

public:
	// ����PCM����(32λ��������)
	// ���������
	//    fpBuffer��PCM������
	//    nSampleCount���������ڵĲ�������
	// ����ֵ�������Ĳ�������
	virtual int Process(float *fpBuffer, int nSampleCount) = 0;

	// ����PCM����(16λ�������ݣ�s16le)
	// ���������
	//    spBuffer��PCM������
	//    nSampleCount���������ڵĲ�������
	// ����ֵ�������Ĳ���������
	virtual int Process(short *spBuffer, int nSampleCount) = 0;

public:
	// �ͷ�ʵ����ע�⣺����ֱ�ӵ��ã�ʹ��ReleaseSurroundInstance���ͷ�
	virtual void Release() = 0;
};

// ����һ������ʵ��������֧�ֶ�ʵ��
ISurround* WINAPI CreateSurroundInstance();

// �ͷŻ���ʵ��
void WINAPI ReleaseSurroundInstance(ISurround *pInstance);


// DynamicVolume�ӿ�
class IDynamicVolume
{
public:
	// ���ö�̬�����Ŀ���ǿ��(1.0~3.5������ʹ��2.5)
	virtual void SetRatio(float nRatio) = 0;

	// ������������(0~1.0)
	virtual void SetVolume(float nVolume) = 0;

	// �������������Ŵ���(1.0~����󣬽���ʹ��8.0)
	virtual void SetMaxGainFactor(float nFactor) = 0;

public:
	// ���ò�����
	virtual void SetSamplingRate(int nSamplingRate) = 0;

	// ������������
	virtual void SetChannels(int nChannels) = 0;

	// ��λЧ������������Seek���л�����ʱ����
	virtual void Reset() = 0;

public:
	// ����PCM����(32λ��������)
	// ���������
	//    fpBuffer��PCM������
	//    nSampleCount���������ڵĲ�������
	// ����ֵ�������Ĳ�������
	virtual int Process(float *fpBuffer, int nSampleCount) = 0;

	// ����PCM����(16λ�������ݣ�s16le)
	// ���������
	//    spBuffer��PCM������
	//    nSampleCount���������ڵĲ�������
	// ����ֵ�������Ĳ���������
	virtual int Process(short *spBuffer, int nSampleCount) = 0;

public:
	// �ͷ�ʵ����ע�⣺����ֱ�ӵ��ã�ʹ��ReleaseDynamicVolumeInstance���ͷ�
	virtual void Release() = 0;
};

// ����һ����̬����ʵ��������֧�ֶ�ʵ��
IDynamicVolume* WINAPI CreateDynamicVolumeInstance();

// �ͷŶ�̬����ʵ��
void WINAPI ReleaseDynamicVolumeInstance(IDynamicVolume *pInstance);


// Limiter�ӿڣ��޷������÷���ο���˵��.docx��
class ILimiter
{
public:
	// ��λЧ������������Seek���л�����ʱ����
	virtual void Reset() = 0;

public:
	// ����PCM����(32λ��������)
	// ���������
	//    fSample��һ��32λ����PCM����
	// ����ֵ��������32λ����PCM����
	virtual float Process(float fSample) = 0;

public:
	// �ͷ�ʵ����ע�⣺����ֱ�ӵ��ã�ʹ��ReleaseLimiterInstance���ͷ�
	virtual void Release() = 0;
};

// ����һ���޷���ʵ��������֧�ֶ�ʵ��
ILimiter* WINAPI CreateLimiterInstance();

// �ͷ��޷���ʵ��
void WINAPI ReleaseLimiterInstance(ILimiter *pInstance);


#endif
