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

// 직렬화된 바이너리 데이터 저장
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;                                // 

	std::string PathString = Path.GetPathToString();        // 저장할 위치 지정
	std::string Text = "wb";                                // w : 쓰기 // b : 바이너리 데이터

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());    // fopen은 파일을 여는 함수

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	// 오픈한 파일에 데이터 입력
	//     버퍼 사이즈           저장할 데이터 사이즈     어디에
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr); // 몇 번 나눌 것인가? >> 안나눌것이기 때문에 1 전달ㄴ

	// 저장이 끝나면 nullptr이 아니기 때문에 닫힌다.
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// 직렬화된 텍스트 데이터 저장
void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;
	std::string PathString = Path.GetPathToString();
	std::string Text = "wt";  // 위와 유사하지만, 여기만 다르다 // w : 쓰기 // t : 텍스트 데이터

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// 직렬화된 바이너리 데이터 불러오기
void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();
	std::string Text = "rb"; // r : 읽기 // b : 바이너리 데이터

	//     이것을      해당경로에서        열어라
	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	// 파일 사이즈는 불러온 파일에 대한 사이즈를 할당
	size_t FileSize = std::filesystem::file_size(Path.Path);

	//      가져온 데이터     버퍼사이즈              읽어야하는 사이즈
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	// 끝나면 종료
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}