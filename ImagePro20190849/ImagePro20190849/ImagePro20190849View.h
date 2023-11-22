
// ImagePro20190849View.h: CImagePro20190849View 클래스의 인터페이스
//

#pragma once


class CImagePro20190849View : public CView
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
	void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다
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
	afx_msg void OnPixelMul();
	afx_msg void OnPixelHistoEqu();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnRegionMeaning();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMonopologyColorToGray();
	afx_msg void OnMonopologyBinarization();
	afx_msg void OnMonopologyErosion();
	afx_msg void OnMonopologyDilation();
	afx_msg void OnMonopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMonopologyClosing();
	afx_msg void OnGeometryZoomPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryAvgSampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGemetryHolizantalFlip();
	afx_msg void OnGeomertVerticalFlip();
	afx_msg void OnGeometryWabping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	CString AviFileName;
	bool bAviMode;
	void LoadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // ImagePro20190849View.cpp의 디버그 버전
inline CImagePro20190849Doc* CImagePro20190849View::GetDocument() const
   { return reinterpret_cast<CImagePro20190849Doc*>(m_pDocument); }
#endif

