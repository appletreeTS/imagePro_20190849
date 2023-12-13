
// ImagePro___20190849View.h: CImagePro20190849View 클래스의 인터페이스
//

#pragma once


class CImagePro20190849View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImagePro20190849View() noexcept;
	DECLARE_DYNCREATE(CImagePro20190849View)

// 특성입니다.
public:
	CImagePro20190849Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImagePro20190849View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixeSub();
	afx_msg void OnPixleMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEqu();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionMeaning();
	int convolve(unsigned char** inputimg, unsigned char** resultimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMonopologyColorToGray();
	afx_msg void OnMonopologyBinarization();
	afx_msg void OnMonopologyErosion();
	afx_msg void OnMonopologyDilation();
	afx_msg void OnMonopologyOpening();
	int CopyResultToInput();
	afx_msg void OnMonopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoomin();
	afx_msg void OnGeometryZoomoutSub();
	afx_msg void OnGeometryMinSub();
	afx_msg void OnGeometryAvgSampling();
	afx_msg void OnGeometryLotation();
	afx_msg void OnGeometryHolizantalFlip();
	afx_msg void OnGeometryVerticalFlip();
	afx_msg void OnGeometryWabping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CString AviFileName;
	bool bAviMode;
	void LoadAviFile(CDC* pDC);
	afx_msg void OnAviView();
	CString imagePath;
	afx_msg void OnGeometryMobping();
};

#ifndef _DEBUG  // ImagePro___20190849View.cpp의 디버그 버전
inline CImagePro20190849Doc* CImagePro20190849View::GetDocument() const
   { return reinterpret_cast<CImagePro20190849Doc*>(m_pDocument); }
#endif

