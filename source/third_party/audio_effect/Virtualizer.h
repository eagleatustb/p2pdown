#ifndef _VIRTUALIZER
#define _VIRTUALIZER

#include <windows.h>

// ���ӿ�
class IVirtualizer
{
public:
	// ����Ч������ͬʱ�趨�����ʡ���������Ч��ģ�͵�ID��������棩
	// ����falseΪʧ��
	virtual bool Active(int nSamplingRate, int nChannels, int nModelID) = 0;
	// ����Ч����
	virtual void Reset() = 0;
	// ����PCM������nFramesΪ��������������ֵ�Ǵ����Ĳ�������
	virtual int Process(float *fpPCMBuffer, int nFrames) = 0;

public:
	// ���ٽӿ�
	virtual void Release() = 0;
};

// ��ʽ֧�ּ��ӿڣ������ʡ���������Ч��ģ�͵�ID��������棩������1Ϊ֧�֣�0Ϊ��֧��
int WINAPI VirtualizerCheckFormat(int nSamplingRate, int nChannels, int nModeID);
// ����Virtualizerʵ��
IVirtualizer* WINAPI CreateVirtualizer();

/*
 * ģ��ID[nModeID]ΪЧ��ѡ���ģ�ͱ��
 * ʵ����1��2����
 *
 * ʹ������Ϊ��
 * CreateVirtualizer -> VirtualizerCheckFormat ->
 * Active -> Process -> Release
 *
 * Virtualizer֧�ֵ���Ƶ��ʽΪ��
 * �����ʣ�44100��48000��88200��96000��176400��192000
 * ��������2
 * ���ڵ����������Ҫ����ʹ������Ҫ������������һ������α������
 *
 * ע�⣺
 *   ������Activeʱ��Virtualizer��ǿ����ջ��桢�ͷŲ����·���һЩ�ڴ�
 *   ͬʱ�������������㣬�����˲��CPU��RAMռ�����ߡ�
 *   ��˽�����������ʻ�ģ��ID�����仯ʱ�ٵ��á�
 */

/*

ʹ�÷�����
// ��ʼ��
{
	// �½�ʵ��
	IVirtualizer *pVirtualizer = CreateVirtualizer();
	if (pVirtualizer == NULL) {
		MessageOut("Failed to create virtualizer instance.");
		return -1;
	}

	// ʹ��Ĭ�ϲ�������Virtualizer
	if (!pVirtualizer->Active(44100, 2, ModelID)) {
		MessageOut("Failed to active virtualizer.");
		return -1;
	}
}

// �и���϶��ص�������ҪResetЧ������ʱ��
void SongSeekCallback()
{
	// ����Virtualizer�ڲ�û��������˶��̻߳�������Ҫԭ�Ӳ���
	EnterCriticalSection();
	// ResetЧ����
	pVirtualizer->Reset();
	LeaveCriticalSection();
}

// ����Ƶ�Ĳ����ʻ��������仯ʱ
void UpdateAudioFormat(int nSamplingRate, int nChannels)
{
	// �������ʺ�������û�б仯����Ҫ����Active
	if ((nSamplingRate == nOldSamplingRate) &&
		(nChannels == nOldChannels))
		return;

	// ����Virtualizer�ڲ�û��������˶��̻߳�������Ҫԭ�Ӳ���
	EnterCriticalSection();
	// ����ʽ֧��
	if (!VirtualizerCheckFormat(nSamplingRate, nChannels, ModelID)) {
		MessageOut("Unsupported audio format.");
		LeaveCriticalSection();
		return;
	}
	// ���¸�ʽ
	if (!pVirtualizer->Active(nSamplingRate, nChannels, ModelID)) {
		MessageOut("Failed to active virtualizer.");
		LeaveCriticalSection();
		return;
	}
	LeaveCriticalSection();

	// ������Ƶ��ʽ
	nOldSamplingRate = nSamplingRate;
	nOldChannels = nChannels;
}

// �����߳�
DWORD ProcessingThread(void *p)
{
	// ������Ƶ����
	float faPCMSamples[BUFFER_LENGTH];
	int nFrames = GetDecoderPCM(faPCMSamples, BUFFER_LENGTH);

	// Ч����������Virtualizer�ڲ�û��������˶��̻߳�������Ҫԭ�Ӳ���
	EnterCriticalSection();
	nFrames = pVirtualizer->Process(faPCMSamples, nFrames);
	LeaveCriticalSection();

	// ������Ч����
	EqualizerProcess(faPCMSamples, nFrames);		// ����������
	DynamicVolumeProcess(faPCMSamples, nFrames);	// ������������
	LimiterProcess(faPCMSamples, nFrames);			// �޷���

	// ���
	AudioOutputWrite(faPCMSamples, nFrames);
}

// ����ʵ��
{
	pVirtualizer->Release();
	pVirtualizer = NULL;
}

ע�⣺
	����ʾ��������ʹ���˶��̻߳����������Ҫ��pVirtualizer���м�����
	��ʵ��Ϊ���̵߳��ã������������

*/


#endif
