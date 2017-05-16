
// Ex1Doc.cpp : implementation of the CEx1Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ex1.h"
#endif

#include "Ex1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEx1Doc

IMPLEMENT_DYNCREATE(CEx1Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx1Doc, CDocument)
END_MESSAGE_MAP()


// CEx1Doc construction/destruction

CEx1Doc::CEx1Doc()
{
	m_transY = 100; m_transX = 100;
	m_angle2 = 15; m_angle1 = 15;


}

CEx1Doc::~CEx1Doc()
{
}

BOOL CEx1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	glNewList(ArmPart, GL_COMPILE); // Microsoft VC++ API
	glBegin(GL_POLYGON);
	glVertex2f(-10.0f, 10.0f);
	glVertex2f(-10.0f, -10.0f);
	glVertex2f(100.0f, -10.0f);
	glVertex2f(100.0f, 10.0f);
	glEnd();
	glEndList();

	return TRUE;
}




// CEx1Doc serialization

void CEx1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		 //TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CEx1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CEx1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CEx1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEx1Doc diagnostics

#ifdef _DEBUG
void CEx1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx1Doc commands
void CEx1Doc::RenderScene(void) {
	//Example 1
	/*glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glCallList(ArmPart);*/
	////Example 2
	 //glPushMatrix();
	 //glTranslated( m_transX, m_transY, 0);
	 //glRotated( m_angle1, 0, 0, 1);
	 //glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	 //glCallList(ArmPart);
	 //glPopMatrix();
	//Example 3
	 /*glPushMatrix();
	 glTranslated( m_transX, m_transY, 0);
	 glRotated( m_angle1, 0, 0, 1);
	 glPushMatrix();
	 glTranslated( 90, 0, 0);
	 glRotated( m_angle2, 0, 0, 1);
	 glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	 glCallList(ArmPart);
		 glPopMatrix();
		 glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		 glCallList(ArmPart);
		 glPopMatrix();
		glFlush();*/
	GLfloat RedSurface[] = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat GreenSurface[] = { 0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat BlueSurface[] = { 0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 0.1f };
	GLfloat LightDiffuse[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.1f };
	GLfloat LightPosition[] = { 15.0f, 15.0f, 5.0f, 0.0f };



	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	//Rysuje sobie punkt
	glBegin(GL_POINTS);
	glVertex3d(1.0f, 0.0f, -5.0f);
	glEnd();
	glEnable(GL_LIGHT0);
	glPushMatrix();
	glTranslated(0.0, 0.0, -8.0);
	glRotated(m_angle1, 1.0, 0.0, 0.0);
	glRotated(m_angle2, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RedSurface);
	glBegin(GL_POLYGON);
	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 1.0, 1.0);
	glVertex3d(1.0, -1.0, 1.0);
	glVertex3d(1.0, -1.0, -1.0);
	glVertex3d(1.0, 1.0, -1.0);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-1.0, -1.0, 1.0);
	glVertex3d(-1.0, 1.0, 1.0);
	glVertex3d(-1.0, 1.0, -1.0);
	glVertex3d(-1.0, -1.0, -1.0);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GreenSurface);
	glBegin(GL_POLYGON);
	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 1.0);
	glVertex3d(-1.0, 1.0, 1.0);
	glVertex3d(-1.0, 1.0, -1.0);
	glVertex3d(1.0, 1.0, -1.0);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3d(0.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, 1.0);
	glVertex3d(1.0, -1.0, 1.0);
	glVertex3d(1.0, -1.0, -1.0);
	glVertex3d(-1.0, -1.0, -1.0);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BlueSurface);
	glBegin(GL_POLYGON);
	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d(1.0, 1.0, 1.0);
	glVertex3d(-1.0, 1.0, 1.0);
	glVertex3d(-1.0, -1.0, 1.0);
	glVertex3d(1.0, -1.0, 1.0);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3d(0.0, 0.0, -1.0);
	glVertex3d(-1.0, 1.0, -1.0);
	glVertex3d(1.0, 1.0, -1.0);
	glVertex3d(1.0, -1.0, -1.0);
	glVertex3d(-1.0, -1.0, -1.0);
	glEnd();
	glPopMatrix();

}