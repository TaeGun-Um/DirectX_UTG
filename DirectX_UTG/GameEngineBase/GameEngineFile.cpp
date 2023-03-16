#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile()
{
}

GameEngineFile::~GameEngineFile()
{
}


GameEngineFile::GameEngineFile(std::filesystem::path _Path)
	: Path(_Path)
{

}

// ����ȭ�� ���̳ʸ� ������ ����
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;                                // 

	std::string PathString = Path.GetPathToString();        // ������ ��ġ ����
	std::string Text = "wb";                                // w : ���� // b : ���̳ʸ� ������

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());    // fopen�� ������ ���� �Լ�

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	// ������ ���Ͽ� ������ �Է�
	//     ���� ������           ������ ������ ������     ���
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr); // �� �� ���� ���ΰ�? >> �ȳ������̱� ������ 1 ���ޤ�

	// ������ ������ nullptr�� �ƴϱ� ������ ������.
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// ����ȭ�� �ؽ�Ʈ ������ ����
void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;
	std::string PathString = Path.GetPathToString();
	std::string Text = "wt";  // ���� ����������, ���⸸ �ٸ��� // w : ���� // t : �ؽ�Ʈ ������

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// ����ȭ�� ���̳ʸ� ������ �ҷ�����
void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();
	std::string Text = "rb"; // r : �б� // b : ���̳ʸ� ������

	//     �̰���      �ش��ο���        �����
	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	// ���� ������� �ҷ��� ���Ͽ� ���� ����� �Ҵ�
	size_t FileSize = std::filesystem::file_size(Path.Path);

	//      ������ ������     ���ۻ�����              �о���ϴ� ������
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	// ������ ����
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}