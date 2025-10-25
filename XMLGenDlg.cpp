
// XMLGenDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "XMLGen.h"
#include "XMLGenDlg.h"
#include "afxdialogex.h"
#include <afxwin.h>              // MFC core and standard components
#include <afxdlgs.h>             // MFC common dialogs (e.g., folder dialog)
#include <afxcmn.h>              // MFC controls (e.g., progress bar, list control)
#include <afxstr.h>              // MFC CString and string manipulation
#include <shlobj.h>              // Windows Shell functions (for folder browsing)
#include <atlstr.h>              // ATL CString (if using ATL strings)
#include <afx.h>                 // MFC standard library (CStdioFile, etc.)
#include <afxext.h>  
#include <atlconv.h> 
#include <string>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXMLGenDlg dialog



CXMLGenDlg::CXMLGenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XMLGEN_DIALOG, pParent)
	, m_Name(_T(""))
	, m_Date(_T(""))
	, m_ST(_T(""))
	, m_ET(_T(""))
	, m_TN(_T(""))
	, m_V1(_T(""))
	, m_V2(_T(""))
	, m_V3(_T(""))
	, m_V4(_T(""))
	, m_V5(_T(""))
	, m_V6(_T(""))
	, m_V7(_T(""))
	, m_TD(_T(""))
	, m_V8(_T(""))
	, m_V9(_T(""))
	, m_V10(_T(""))
	, m_V11(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Text(pDX, IDC_EDIT3, m_Date);
	DDX_Text(pDX, IDC_EDIT5, m_ST);
	DDX_Text(pDX, IDC_EDIT4, m_ET);
	DDX_Control(pDX, IDC_COMBO7, m_P);
	DDX_Control(pDX, IDC_COMBO5, m_TT);
	DDX_Control(pDX, IDC_COMBO1, m_TSD);
	DDX_Control(pDX, IDC_COMBO6, m_E);
	DDX_Control(pDX, IDC_COMBO3, m_A);
	DDX_Control(pDX, IDC_COMBO4, m_C);
	DDX_Text(pDX, IDC_EDIT18, m_TN);
	DDX_Text(pDX, IDC_EDIT7, m_V1);
	DDX_Text(pDX, IDC_EDIT6, m_V2);
	DDX_Text(pDX, IDC_EDIT9, m_V3);
	DDX_Text(pDX, IDC_EDIT8, m_V4);
	DDX_Text(pDX, IDC_EDIT13, m_V5);
	DDX_Text(pDX, IDC_EDIT11, m_V6);
	DDX_Text(pDX, IDC_EDIT15, m_V7);
	DDX_Text(pDX, IDC_EDIT12, m_TD);
	DDX_Text(pDX, IDC_EDIT10, m_V8);
	DDX_Text(pDX, IDC_EDIT14, m_V9);
	DDX_Text(pDX, IDC_EDIT16, m_V10);
	DDX_Text(pDX, IDC_EDIT17, m_V11);
    DDX_Control(pDX, IDC_COMBO4, m_C);
}

BEGIN_MESSAGE_MAP(CXMLGenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO4, &CXMLGenDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON1, &CXMLGenDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CXMLGenDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CXMLGenDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CXMLGenDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_PauseButton, &CXMLGenDlg::OnBnClickedPausebutton)
    ON_BN_CLICKED(IDC_PlayButton, &CXMLGenDlg::OnBnClickedPlaybutton)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_VIDEO_SLIDER, &CXMLGenDlg::OnNMCustomdrawVideoSlider)
END_MESSAGE_MAP()


// CXMLGenDlg message handlers

BOOL CXMLGenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_P.AddString(_T("EO"));
	m_P.AddString(_T("SAR"));
	m_P.AddString(_T("MPAR"));
	m_P.AddString(_T("ELINT"));
	m_P.AddString(_T("COMINT"));

	m_TT.AddString(_T("Building"));
	m_TT.AddString(_T("Bridge"));
	m_TT.AddString(_T("Sub Station"));
	m_TT.AddString(_T("Petrol Bunk"));
	m_TT.AddString(_T("Runway"));
	m_TT.AddString(_T("Road Junction"));
	m_TT.AddString(_T("Water Body"));
	m_TT.AddString(_T("Vehicle"));
	m_TT.AddString(_T("People"));
	m_TT.AddString(_T("Animal"));

	m_TSD.AddString(_T("Static"));
	m_TSD.AddString(_T("Dynamic"));

	m_E.AddString(_T("Laser Firing"));
	m_E.AddString(_T("Vehicle Tracking"));
	m_E.AddString(_T("take Off"));
	m_E.AddString(_T("landing"));
	m_E.AddString(_T("Hovering"));
	m_E.AddString(_T("Rolling"));
	m_E.AddString(_T("Climbing"));

	m_A.AddString(_T("Roll"));
	m_A.AddString(_T("Pitch"));
	m_A.AddString(_T("Hdg"));
	m_A.AddString(_T("Alt"));

	m_C.AddString(_T("Azimuth"));
	m_C.AddString(_T("Elivation"));
	m_C.AddString(_T("FOV"));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMLGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMLGenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMLGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXMLGenDlg::OnCbnSelchangeCombo4()
{
	// TODO: Add your control notification handler code here
}


void CXMLGenDlg::OnBnClickedButton1()
{
    static bool isFileCreated = false; // Track whether the file has been created
    static CString filePath; // Store the full file path

    UpdateData(TRUE);

    // Mandatory fields
    CString name = m_Name.IsEmpty() ? _T("None") : m_Name;
    CString date = m_Date.IsEmpty() ? _T("None") : m_Date;
    CString startTime = m_ST.IsEmpty() ? _T("None") : m_ST;
    CString endTime = m_ET.IsEmpty() ? _T("None") : m_ET;

    CString payloadName = _T("None");
    CString targetType = _T("None");
    CString targetSD = _T("None");
    CString eventType = _T("None");
    CString aircraftName = _T("None");
    CString cameraName = _T("None");

    // Get selected item from ComboBoxes (if any)
    if (m_P.GetCurSel() != CB_ERR) {
        m_P.GetLBText(m_P.GetCurSel(), payloadName);
    }

    if (m_TT.GetCurSel() != CB_ERR) {
        m_TT.GetLBText(m_TT.GetCurSel(), targetType);
    }

    if (m_TSD.GetCurSel() != CB_ERR) {
        m_TSD.GetLBText(m_TSD.GetCurSel(), targetSD);
    }

    if (m_E.GetCurSel() != CB_ERR) {
        m_E.GetLBText(m_E.GetCurSel(), eventType);
    }

    if (m_A.GetCurSel() != CB_ERR) {
        m_A.GetLBText(m_A.GetCurSel(), aircraftName);
    }

    if (m_C.GetCurSel() != CB_ERR) {
        m_C.GetLBText(m_C.GetCurSel(), cameraName);
    }

    CString targetName = m_TN.IsEmpty() ? _T("None") : m_TN;
    CString v1 = m_V1.IsEmpty() ? _T("None") : m_V1;
    CString v2 = m_V2.IsEmpty() ? _T("None") : m_V2;
    CString v3 = m_V3.IsEmpty() ? _T("None") : m_V3;
    CString v4 = m_V4.IsEmpty() ? _T("None") : m_V4;
    CString v5 = m_V5.IsEmpty() ? _T("None") : m_V5;
    CString v6 = m_V6.IsEmpty() ? _T("None") : m_V6;
    CString v7 = m_V7.IsEmpty() ? _T("None") : m_V7;
    CString targetDescription = m_TD.IsEmpty() ? _T("None") : m_TD;
    CString v8 = m_V8.IsEmpty() ? _T("None") : m_V8;
    CString v9 = m_V9.IsEmpty() ? _T("None") : m_V9;
    CString v10 = m_V10.IsEmpty() ? _T("None") : m_V10;
    CString v11 = m_V11.IsEmpty() ? _T("None") : m_V11;

    // Generate the XML content for the new Target
    CString targetContent;
    targetContent.Format(_T("\t<Target>\n")
        _T("\t\t<Type>%s</Type>\n")
        _T("\t\t<SD>%s</SD>\n")
        _T("\t\t<Name>%s</Name>\n")
        _T("\t\t<Start_Time>%s</Start_Time>\n")
        _T("\t\t<End_Time>%s</End_Time>\n")
        _T("\t\t<Latitude>%s</Latitude>\n")
        _T("\t\t<Longitude>%s</Longitude>\n")
        _T("\t\t<Altitude>%s</Altitude>\n")
        _T("\t\t<Event>\n")
        _T("\t\t\t<Type>%s</Type>\n")
        _T("\t\t\t<Start_Time>%s</Start_Time>\n")
        _T("\t\t\t<End_Time>%s</End_Time>\n")
        _T("\t\t</Event>\n")
        _T("\t\t<Description>%s</Description>\n")
        _T("\t</Target>\n"),
        targetType, targetSD, targetName, v1, v2, v3, v4, v5,
        eventType, v6, v7, targetDescription);

    // Generate content for Aircraft and Camera
    CString aircraftContent, cameraContent;
    aircraftContent.Format(_T("\t<Aircraft>\n")
        _T("\t\t<Name>%s</Name>\n")
        _T("\t\t<Min>%s</Min>\n")
        _T("\t\t<Max>%s</Max>\n")
        _T("\t</Aircraft>\n"),
        aircraftName, v8, v9);

    cameraContent.Format(_T("\t<Camera>\n")
        _T("\t\t<Name>%s</Name>\n")
        _T("\t\t<Min>%s</Min>\n")
        _T("\t\t<Max>%s</Max>\n")
        _T("\t</Camera>\n"),
        cameraName, v10, v11);

    // Prompt for directory on first press
    if (!isFileCreated)
    {
        CFileDialog dlg(FALSE, _T("xml"), _T("output.xml"),
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
            _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||"));

        if (dlg.DoModal() == IDOK)
        {
            filePath = dlg.GetPathName();
        }
        else
        {
            return; // User canceled the dialog
        }

        // First press: Create the file with the root structure
        CString fileContent;
        fileContent.Format(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
            _T("<Schedule>\n")
            _T("\t<Name>%s</Name>\n")
            _T("\t<Date>%s</Date>\n")
            _T("\t<Start_Time>%s</Start_Time>\n")
            _T("\t<End_Time>%s</End_Time>\n")
            _T("\t<Payload>\n")
            _T("\t\t<Name>%s</Name>\n")
            _T("\t</Payload>\n")
            _T("%s%s%s</Schedule>\n"),
            name, date, startTime, endTime, payloadName, targetContent,
            aircraftContent, cameraContent);

        CStdioFile file;
        if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
        {
            file.WriteString(fileContent);
            file.Close();
        }

        isFileCreated = true;
    }
    else
    {
        // Subsequent presses: Append content within the root tags
        CString existingContent;

        CStdioFile file;
        if (file.Open(filePath, CFile::modeReadWrite | CFile::typeText))
        {
            CString line;
            while (file.ReadString(line))
            {
                if (line.Find(_T("</Schedule>")) == -1) // Exclude the closing tag
                {
                    existingContent += line + _T("\n");
                }
            }
            file.Close();
        }

        existingContent += targetContent + aircraftContent + cameraContent + _T("</Schedule>\n");

        // Write back the updated content
        if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
        {
            file.WriteString(existingContent);
            file.Close();
        }
    }

    // Reset fields for the next input
    m_TN.Empty();
    m_V1.Empty();
    m_V2.Empty();
    m_V3.Empty();
    m_V4.Empty();
    m_V5.Empty();
    m_V6.Empty();
    m_V7.Empty();
    m_TD.Empty();
    m_V8.Empty();
    m_V9.Empty();
    m_V10.Empty();
    m_V11.Empty();
    m_P.SetCurSel(-1);
    m_TT.SetCurSel(-1);
    m_TSD.SetCurSel(-1);
    m_E.SetCurSel(-1);
    m_A.SetCurSel(-1);
    m_C.SetCurSel(-1);

    UpdateData(FALSE);
}


void CXMLGenDlg::OnBnClickedButton3()
{
    UpdateData(TRUE);

    // Retrieve ComboBox values directly from member variables
    CString name = m_Name;
    CString date = m_Date;
    CString startTime = m_ST;
    CString endTime = m_ET;
    CString targetName = m_TN;
    CString v1 = m_V1;
    CString v2 = m_V2;
    CString v3 = m_V3;
    CString v4 = m_V4;
    CString v5 = m_V5;
    CString v6 = m_V6;
    CString v7 = m_V7;
    CString targetDescription = m_TD;
    CString v8 = m_V8;
    CString v9 = m_V9;
    CString v10 = m_V10;
    CString v11 = m_V11;

    CString payloadName, targetType, targetSD, eventType, aircraftName, cameraName;

    // Get selected item from ComboBoxes (if any)
    if (m_P.GetCurSel() != CB_ERR) {
        m_P.GetLBText(m_P.GetCurSel(), payloadName);
    }
    else {
        payloadName = _T("None");
    }

    if (m_TT.GetCurSel() != CB_ERR) {
        m_TT.GetLBText(m_TT.GetCurSel(), targetType);
    }
    else {
        targetType = _T("None");
    }

    if (m_TSD.GetCurSel() != CB_ERR) {
        m_TSD.GetLBText(m_TSD.GetCurSel(), targetSD);
    }
    else {
        targetSD = _T("None");
    }

    if (m_E.GetCurSel() != CB_ERR) {
        m_E.GetLBText(m_E.GetCurSel(), eventType);
    }
    else {
        eventType = _T("None");
    }

    if (m_A.GetCurSel() != CB_ERR) {
        m_A.GetLBText(m_A.GetCurSel(), aircraftName);
    }
    else {
        aircraftName = _T("None");
    }

    if (m_C.GetCurSel() != CB_ERR) {
        m_C.GetLBText(m_C.GetCurSel(), cameraName);
    }
    else {
        cameraName = _T("None");
    }

    // Default to "None" if the text is empty
    if (name.IsEmpty()) name = _T("None");
    if (date.IsEmpty()) date = _T("None");
    if (startTime.IsEmpty()) startTime = _T("None");
    if (endTime.IsEmpty()) endTime = _T("None");
    if (targetName.IsEmpty()) targetName = _T("None");
    if (v1.IsEmpty()) v1 = _T("None");
    if (v2.IsEmpty()) v2 = _T("None");
    if (v3.IsEmpty()) v3 = _T("None");
    if (v4.IsEmpty()) v4 = _T("None");
    if (v5.IsEmpty()) v5 = _T("None");
    if (v6.IsEmpty()) v6 = _T("None");
    if (v7.IsEmpty()) v7 = _T("None");
    if (targetDescription.IsEmpty()) targetDescription = _T("None");
    if (v8.IsEmpty()) v8 = _T("None");
    if (v9.IsEmpty()) v9 = _T("None");
    if (v10.IsEmpty()) v10 = _T("None");
    if (v11.IsEmpty()) v11 = _T("None");

    // Let the user select a folder to save the XML file
    CString folderPath;
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = _T("Select Folder to Save XML");
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0)
    {
        // Get the folder path
        SHGetPathFromIDList(pidl, folderPath.GetBuffer(MAX_PATH));
        folderPath.ReleaseBuffer();

        // Find the next available file name (output1.xml, output2.xml, etc.)
        int fileIndex = 1;
        CString filePath;
        do {
            filePath.Format(_T("%s\\output%d.xml"), folderPath, fileIndex);
            fileIndex++;
        } while (_taccess(filePath, 0) == 0); // Check if file already exists (0 means file exists)

        // Define the XML schema with actual variables
        CString xmlContent;
        xmlContent.Format(
            _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
            _T("<Schedule>\n")
            _T("\t<Name>%s</Name>\n")
            _T("\t<Date>%s</Date>\n")
            _T("\t<Start_Time>%s</Start_Time>\n")
            _T("\t<End_Time>%s</End_Time>\n")
            _T("\t<Payload>\n")
            _T("\t\t<Name>%s</Name>\n")
            _T("\t</Payload>\n")
            _T("\t<Target>\n")
            _T("\t\t<Type>%s</Type>\n")
            _T("\t\t<SD>%s</SD>\n")
            _T("\t\t<Name>%s</Name>\n")
            _T("\t\t<Start_Time>%s</Start_Time>\n")
            _T("\t\t<End_Time>%s</End_Time>\n")
            _T("\t\t<Latitude>%s</Latitude>\n")
            _T("\t\t<Longitude>%s</Longitude>\n")
            _T("\t\t<Altitude>%s</Altitude>\n")
            _T("\t\t<Event>\n")
            _T("\t\t\t<Type>%s</Type>\n")
            _T("\t\t\t<Start_Time>%s</Start_Time>\n")
            _T("\t\t\t<End_Time>%s</End_Time>\n")
            _T("\t\t</Event>\n")
            _T("\t\t<Description>%s</Description>\n")
            _T("\t</Target>\n")
            _T("\t<Aircraft>\n")
            _T("\t\t<Name>%s</Name>\n")
            _T("\t\t<Min>%s</Min>\n")
            _T("\t\t<Max>%s</Max>\n")
            _T("\t</Aircraft>\n")
            _T("\t<Camera>\n")
            _T("\t\t<Name>%s</Name>\n")
            _T("\t\t<Min>%s</Min>\n")
            _T("\t\t<Max>%s</Max>\n")
            _T("\t</Camera>\n")
            _T("</Schedule>"),
            name, date, startTime, endTime, payloadName, targetType, targetSD, targetName, v1, v2, v3, v4, v5, eventType, v6, v7, targetDescription, aircraftName, v8, v9, cameraName, v10, v11);

        // Write the XML content to the file
        CStdioFile file;
        if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
        {
            file.WriteString(xmlContent);
            file.Close();
            AfxMessageBox(_T("XML file saved successfully in the selected folder."));

            // After saving, clear all fields for new data entry
            m_Name.Empty();
            m_Date.Empty();
            m_ST.Empty();
            m_ET.Empty();
            m_TN.Empty();
            m_V1.Empty();
            m_V2.Empty();
            m_V3.Empty();
            m_V4.Empty();
            m_V5.Empty();
            m_V6.Empty();
            m_V7.Empty();
            m_TD.Empty();
            m_V8.Empty();
            m_V9.Empty();
            m_V10.Empty();
            m_V11.Empty();

            m_P.SetCurSel(-1); m_TT.SetCurSel(-1); m_TSD.SetCurSel(-1);
            m_E.SetCurSel(-1); m_A.SetCurSel(-1); m_C.SetCurSel(-1);

            // Update the dialog with cleared values
            UpdateData(FALSE);
        }
        else
        {
            AfxMessageBox(_T("Failed to save the XML file."));
        }
    }
    else
    {
        AfxMessageBox(_T("Folder selection was cancelled."));
    }
}


// Member variable to control video playback
bool playVideo = true;
int videoPosition = 0; // Current video position in milliseconds

void CXMLGenDlg::OnBnClickedPlaybutton()
{
    playVideo = true; // Resume playback
}

void CXMLGenDlg::OnBnClickedPausebutton()
{
    playVideo = false; // Pause playback
}

void CXMLGenDlg::OnNMCustomdrawVideoSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_VIDEO_SLIDER);
    if (pSlider)
    {
        videoPosition = pSlider->GetPos(); // Set video position based on slider
        playVideo = true; // Resume playback if paused
    }
}


void CXMLGenDlg::OnBnClickedButton4()
{
    // Open file dialog to select a video file
    CFileDialog fileDialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST,
        _T("Video Files (*.mp4;*.avi;*.mov)|*.mp4;*.avi;*.mov|All Files (*.*)|*.*||"));

    if (fileDialog.DoModal() != IDOK)
    {
        MessageBox(_T("No file selected."), _T("Information"), MB_ICONINFORMATION);
        return;
    }

    CString filePath = fileDialog.GetPathName();
    std::string chosenFile = CW2A(filePath);

    // Open the video file
    cv::VideoCapture objcap(chosenFile);
    if (!objcap.isOpened())
    {
        MessageBox(_T("Unable to open video file."), _T("Error"), MB_ICONERROR);
        return;
    }

    // Get the video's total duration in milliseconds
    int totalFrames = static_cast<int>(objcap.get(cv::CAP_PROP_FRAME_COUNT));
    double fps = objcap.get(cv::CAP_PROP_FPS);
    int videoDuration = static_cast<int>((totalFrames / fps) * 1000); // Total duration in milliseconds

    // Configure the slider
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_VIDEO_SLIDER);
    if (pSlider)
    {
        pSlider->SetRange(0, videoDuration); // Set slider range
        pSlider->SetTicFreq(1000); // Tick every second
    }

    // Get the dimensions of the CStatic control
    CStatic* pPictureControl = (CStatic*)GetDlgItem(IDC_VIDEO_DISPLAY);
    CRect rect;
    pPictureControl->GetClientRect(&rect);

    int controlWidth = rect.Width();
    int controlHeight = rect.Height();

    cv::Mat frame, resizedFrame;

    // Get the HDC of the CStatic control
    HDC hdc = ::GetDC(pPictureControl->GetSafeHwnd());

    while (true)
    {
        if (playVideo)
        {
            // Seek to the desired position if the slider was moved
            if (videoPosition > 0)
            {
                objcap.set(cv::CAP_PROP_POS_MSEC, videoPosition);
                videoPosition = 0; // Reset the position flag
            }

            objcap >> frame; // Read the next frame
            if (frame.empty())
                break;

            // Update the slider's position
            if (pSlider)
            {
                int currentPos = static_cast<int>(objcap.get(cv::CAP_PROP_POS_MSEC));
                pSlider->SetPos(currentPos);
            }

            // Resize the frame to fit the picture control
            cv::resize(frame, resizedFrame, cv::Size(controlWidth, controlHeight), 0, 0, cv::INTER_LINEAR);

            // Convert the frame to a format compatible with GDI
            cv::Mat bgrFrame;
            cv::cvtColor(resizedFrame, bgrFrame, cv::COLOR_BGR2BGRA); // Add alpha channel

            // Create a GDI-compatible bitmap
            HBITMAP hBitmap = CreateBitmap(controlWidth, controlHeight, 1, 32, bgrFrame.data);

            // Create a compatible device context
            HDC memDC = CreateCompatibleDC(hdc);
            SelectObject(memDC, hBitmap);

            // Blit the frame onto the picture control
            BitBlt(hdc, 0, 0, controlWidth, controlHeight, memDC, 0, 0, SRCCOPY);

            // Cleanup
            DeleteObject(hBitmap);
            DeleteDC(memDC);
        }

        // Check for user input (exit if ESC is pressed)
        if (cv::waitKey(30) == 27)
            break;
    }

    // Cleanup
    ::ReleaseDC(pPictureControl->GetSafeHwnd(), hdc);
    objcap.release();
}



void CXMLGenDlg::OnBnClickedButton2()
{
    // Close the file if it's open
    static CString filePath; // Store the full file path (to close the file)
    static bool isFileCreated = false;

    if (isFileCreated)
    {
        // We need to close the file if it's open
        CStdioFile file;
        if (file.Open(filePath, CFile::modeReadWrite | CFile::typeText))
        {
            // Optionally, save any final content or finalize the file before closing (optional step)
            file.Close();
        }
        isFileCreated = false; // Reset the file creation flag
    }

    // Any additional logic you want to implement for Button2

    // For example, if you want to display a message indicating the file has been closed:
    AfxMessageBox(_T("The file has been closed and the data is finalized."));
}






