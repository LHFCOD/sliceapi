#include "MicroComDocIO.h"
using namespace MicroComDoc;
#include <vector>

ComDocIO::ComDocIO(QString RootDir)
{
	::OleInitialize(NULL);
	wchar_t wpath[100] = { 0 };
	RootDir.toWCharArray(wpath);
	HRESULT hr = StgOpenStorage(wpath, NULL, STGM_READ | STGM_SHARE_DENY_WRITE, NULL, 0, &rootSt);
	if (FAILED(hr))
	{
		throw std::exception("Read MDS file error!");
	}
}
FileBlock* ComDocIO::ReadFromPath(QString path)
{
	QStringList dirList = path.split("\\");
	//��·���Ϸ��Խ��м��
	for (int i = 0; i < dirList.count(); i++)
	{
		if (i == 0)
		{
			if (!dirList[i].isEmpty())
				throw std::exception("path has error!");
		}
		else
		{
			if (dirList[i].isEmpty())
				throw std::exception("path has error!");
		}
	}
	IStorage *parentSt = rootSt;
	std::vector<IStorage*> StVec;
	for (int i = 1; i < dirList.count() - 1; i++)
	{
		IStorage *childSt;
		//��Ŀ¼����ת��Ϊ���ַ�
		wchar_t wpath[100] = { 0 };
		dirList[i].toWCharArray(wpath);
		HRESULT hr = parentSt->OpenStorage(wpath, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &childSt);
		if (FAILED(hr))
		{
			throw std::exception("Read MDS file error!");
		}
		parentSt = childSt;
		//���Storage����ĸ¼����
		StVec.insert(StVec.end(), parentSt);
	}
	wchar_t wpath[100] = { 0 };
	dirList.last().toWCharArray(wpath);
	IStream* pStream;
	HRESULT hr = parentSt->OpenStream(wpath, 0, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
	if (FAILED(hr))
	{
		throw std::exception("Read MDS file error!");
	}
	//��ȡ����Ϣ
	STATSTG stg;
	pStream->Stat(&stg, NULL);
	char* content = (char*)malloc(stg.cbSize.QuadPart);
	unsigned long readEd = 0;
	pStream->Read(content, stg.cbSize.QuadPart, &readEd);
	//�����ͷŵ�
	pStream->Release();
	//�Ѹ�Ŀ¼�ͷŵ�
	for(auto *st : StVec)
	{
		if (st != nullptr)
			st->Release();
	}
	return new FileBlock((byte_t*)content, stg.cbSize.QuadPart);
}

ComDocIO::~ComDocIO()
{
	if (rootSt != nullptr)
	{
		rootSt->Release();
		rootSt = nullptr;
	}
	::OleUninitialize();
}
