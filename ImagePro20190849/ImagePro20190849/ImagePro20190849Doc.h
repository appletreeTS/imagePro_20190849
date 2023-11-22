
// ImagePro20190849Doc.h: CImagePro20190849Doc 클래스의 인터페이스
//


#pragma once


class CImagePro20190849Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImagePro20190849Doc() noexcept;
	DECLARE_DYNCREATE(CImagePro20190849Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImagePro20190849Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	
	// 입력이미지
	unsigned char** inputImg;		// [y][x]
	unsigned char** inputImg2;		// [y][x]
	// 출력이미지
	unsigned char** resultImg;		// [y][x]
	int imageWidth;
	int imageHeight;
	int depth;		// 1=흑백,3=칼라

	int gImageWidth;
	int gImageHeight;
	// 출력이미지
	unsigned char** gResultImg;		// [y][x]

	int LoadImageFile(CArchive& ar)
	{
		int maxValue, i;
		char type[16], buf[256];
		CFile* fp = ar.GetFile();
		CString fname = fp->GetFilePath();
		bool isbmp = false;

		if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
			strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
		{
			ar.ReadString(type, 15);
			do {
				ar.ReadString(buf, 255);
			} while (buf[0] == '#');
			sscanf(buf, "%d %d", &imageWidth, &imageHeight);

			do {
				ar.ReadString(buf, 255);
			} while (buf[0] == '#');
			sscanf(buf, "%d", &maxValue);

			if (strcmp(type, "P5") == 0)	depth = 1;
			else                            depth = 3;
		}
		else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
		{
			//bitmap file header읽기
			BITMAPFILEHEADER bmfh;
			ar.Read((LPSTR)&bmfh, sizeof(bmfh));
			//bmp화일임을 나타내는 "BM"마커가 있는지 확인
			if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))		return 0;

			//bitmap info header읽기
			BITMAPINFOHEADER bih;
			ar.Read((LPSTR)&bih, sizeof(bih));
			imageWidth = bih.biWidth;
			imageHeight = bih.biHeight;
			depth = bih.biBitCount / 8;

			//palette처리
			if (depth == 1)
			{	//palette존재
				BYTE palette[256 * 4];
				ar.Read(palette, 256 * 4);
			}
			isbmp = true;
		}
		else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
		{
			imageWidth = 256;
			imageHeight = 256;
			depth = 1;
		}

		// 메모리 할당
		inputImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
		resultImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
		for (i = 0; i < imageHeight; i++)
		{
			inputImg[i] = (unsigned char*)malloc(imageWidth * depth);
			resultImg[i] = (unsigned char*)malloc(imageWidth * depth);
		}

		if (!isbmp)
		{
			// 파일에서 읽어서 저장
			for (i = 0; i < imageHeight; i++)
				ar.Read(inputImg[i], imageWidth * depth);
		}
		else
		{
			// 파일에서 읽어서 저장
			BYTE nu[4 * 3];
			int widthfile;
			widthfile = (imageWidth * 8 + 31) / 32 * 4;
			for (i = 0; i < imageHeight; i++)
			{
				if (depth == 1)
					ar.Read(inputImg[imageHeight - 1 - i], imageWidth * depth);
				else
				{
					// BGR=>RGB
					BYTE r, g, b;
					for (int j = 0; j < imageWidth; j++)
					{
						ar.Read(&b, 1);	ar.Read(&g, 1);	ar.Read(&r, 1);
						inputImg[imageHeight - 1 - i][3 * j + 0] = r;
						inputImg[imageHeight - 1 - i][3 * j + 1] = g;
						inputImg[imageHeight - 1 - i][3 * j + 2] = b;
					}
				}

				if ((widthfile - imageWidth) != 0)
					ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}

		return 0;
	}
	int LoadSecondImageFile(CArchive& ar)
	{
		int w, h, d;
		int maxValue, i;
		char type[16], buf[256];
		CFile* fp = ar.GetFile();
		CString fname = fp->GetFilePath();
		bool isbmp = false;

		if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
			strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
		{
			ar.ReadString(type, 15);
			do {
				ar.ReadString(buf, 255);
			} while (buf[0] == '#');
			sscanf(buf, "%d %d", &w, &h);

			do {
				ar.ReadString(buf, 255);
			} while (buf[0] == '#');
			sscanf(buf, "%d", &maxValue);

			if (strcmp(type, "P5") == 0)	d = 1;
			else                            d = 3;
		}
		else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
		{
			//bitmap file header읽기
			BITMAPFILEHEADER bmfh;
			ar.Read((LPSTR)&bmfh, sizeof(bmfh));
			//bmp화일임을 나타내는 "BM"마커가 있는지 확인
			if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))		return 0;

			//bitmap info header읽기
			BITMAPINFOHEADER bih;
			ar.Read((LPSTR)&bih, sizeof(bih));
			w = bih.biWidth;
			h = bih.biHeight;
			d = bih.biBitCount / 8;

			//palette처리
			if (d == 1)
			{	//palette존재
				BYTE palette[256 * 4];
				ar.Read(palette, 256 * 4);
			}
			isbmp = true;
		}
		else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
		{
			w = 256;
			h = 256;
			d = 1;
		}

		if (imageWidth != w || imageHeight != h || depth != d)
		{
			AfxMessageBox("가로,세로,색상수가 같아야만 처리할수 있습니다.");
			return 0;
		}

		// 메모리 할당
		inputImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
		for (i = 0; i < imageHeight; i++)
		{
			inputImg2[i] = (unsigned char*)malloc(imageWidth * depth);
		}

		if (!isbmp)
		{
			// 파일에서 읽어서 저장
			for (i = 0; i < imageHeight; i++)
				ar.Read(inputImg2[i], imageWidth * depth);
		}
		else
		{
			// 파일에서 읽어서 저장
			BYTE nu[4 * 3];
			int widthfile;
			widthfile = (imageWidth * 8 + 31) / 32 * 4;
			for (i = 0; i < imageHeight; i++)
			{
				if (depth == 1)
					ar.Read(inputImg2[imageHeight - 1 - i], imageWidth * depth);
				else
				{
					// BGR=>RGB
					BYTE r, g, b;
					for (int j = 0; j < imageWidth; j++)
					{
						ar.Read(&b, 1);	ar.Read(&g, 1);	ar.Read(&r, 1);
						inputImg2[imageHeight - 1 - i][3 * j + 0] = r;
						inputImg2[imageHeight - 1 - i][3 * j + 1] = g;
						inputImg2[imageHeight - 1 - i][3 * j + 2] = b;
					}
				}

				if ((widthfile - imageWidth) != 0)
					ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}

		return 0;
	}
};
