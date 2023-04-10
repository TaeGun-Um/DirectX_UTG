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

// 간간히 윈도우 사용 중 파일을 열 때, "다른 ~가 사용중"이라고 뜨는 것은 fopen가 해당 파일을 잡아채고 있기 때문이다.
// fopen  : 경로의 파일을 열어서 수정하도록 함
// fwrite : 파일 수정
// fread  : 파일 불러오기

// w : wirte, 파일을 쓰고 만약 해당 경로에 파일이 존재하지 않으면 만들겠다.
// r : read, 파일을 읽는다
// t : text, 텍스트 형식, 67을 저장하면 "a"로 저장된다.
// b : binary, 바이너리 형식, 67을 저장하면 1010101... 로 저장된다.


// 직렬화된 바이너리 데이터 저장
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;                                // C스타일 파일 저장 형식으로 진행할 예정

	std::string PathString = Path.GetPathToString();        // FileName 지정
	std::string Text = "wb";                                // 어떤 형식으로 작업을 진행

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());    // 1. FilePtr이 들어가면 값이 바뀌어서 나온다 2. FileName 전달 3. 작업 진행 방식

	// 여기까지 진행하면 파일에 대해 fopen_s 함수가 파일을 수정하고 있는 상황이다.
	// 고로 fclose를 실시하여 fopen 실행을 멈춰줘야 함

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
	std::string Text = "wt";

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
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	// 파일의 크기를 알아내고, 시리얼라이저를 키워서 읽어오는 인터페이스 구성
	// std::filesystem::file_size() == 경로의 파일에 대한 크기를 가져옴
	size_t FileSize = std::filesystem::file_size(Path.Path);

	//      여기에 복사해줘라  버퍼사이즈              읽어야하는 사이즈
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	// 끝나면 종료
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}