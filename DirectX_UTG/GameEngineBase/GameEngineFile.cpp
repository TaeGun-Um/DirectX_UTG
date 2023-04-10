#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
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

// ������ ������ ��� �� ������ �� ��, "�ٸ� ~�� �����"�̶�� �ߴ� ���� fopen�� �ش� ������ ���ä�� �ֱ� �����̴�.
// fopen  : ����� ������ ��� �����ϵ��� ��
// fwrite : ���� ����
// fread  : ���� �ҷ�����

// w : wirte, ������ ���� ���� �ش� ��ο� ������ �������� ������ ����ڴ�.
// r : read, ������ �д´�
// t : text, �ؽ�Ʈ ����, 67�� �����ϸ� "a"�� ����ȴ�.
// b : binary, ���̳ʸ� ����, 67�� �����ϸ� 1010101... �� ����ȴ�.


// ����ȭ�� ���̳ʸ� ������ ����
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;                                // C��Ÿ�� ���� ���� �������� ������ ����

	std::string PathString = Path.GetPathToString();        // FileName ����
	std::string Text = "wb";                                // � �������� �۾��� ����

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());    // 1. FilePtr�� ���� ���� �ٲ� ���´� 2. FileName ���� 3. �۾� ���� ���

	// ������� �����ϸ� ���Ͽ� ���� fopen_s �Լ��� ������ �����ϰ� �ִ� ��Ȳ�̴�.
	// ��� fclose�� �ǽ��Ͽ� fopen ������ ������� ��

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
	std::string Text = "wt";

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
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	// ������ ũ�⸦ �˾Ƴ���, �ø���������� Ű���� �о���� �������̽� ����
	// std::filesystem::file_size() == ����� ���Ͽ� ���� ũ�⸦ ������
	size_t FileSize = std::filesystem::file_size(Path.Path);

	//      ���⿡ ���������  ���ۻ�����              �о���ϴ� ������
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	// ������ ����
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}