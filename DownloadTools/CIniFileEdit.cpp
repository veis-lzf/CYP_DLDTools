#include "pch.h"
#include "CIniFileEdit.h"

CIniFileEdit::CIniFileEdit(LPCTSTR file)
{
    m_pCfgFile = file;
}

CIniFileEdit::~CIniFileEdit()
{
}

/*
 * @brief：设置本地INI配置文件路径
 * @param：
 *      handle：INI配置文件路径
 **/
void CIniFileEdit::SetFileHandle(LPCTSTR handle)
{
    m_pCfgFile = handle;
}

/*
 * @brief：获取本地INI配置文件路径
 * @return：返回m_pCfgFile的值，若用户未初始化则缺省为NULL
 **/
LPCTSTR CIniFileEdit::GetFileHandle(void)
{
    return m_pCfgFile;
}

/*
 * @brief：获取字符串键值
 * @param：
 *      pCfg：键值结构体
 *      szReturn：返回值缓冲区
 * @return：返回值是复制到缓冲区的字符数，不包括空终止字符
 **/
DWORD CIniFileEdit::GetProfileString(CfgStrStruct* pCfg, CString& szReturn)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    pCfg->lpString = NULL; // 缺省值设置为NULL
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::GetPrivateProfileString(pCfg->lpAppName, pCfg->lpKeyName, pCfg->lpString, 
        szReturn.GetBuffer(MAX_PATH), MAX_PATH, fileName);
}

/*
 * @brief：把键值写入本地INI配置文件
 * @param：
 *      pCfg：键值结构体，详情见@CfgIntStruct
 * @return：成功返回TRUE，否则返回FALSE
 **/
BOOL CIniFileEdit::SetProfileString(CfgStrStruct* pCfg)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(pCfg->lpAppName, pCfg->lpKeyName, pCfg->lpString, fileName);
}

/*
 * @brief：获取字符串键值
 * @param：
 *      pCfg：键值结构体
 *      nDefault：默认返回值（注：当读取不到键值时，默认返回）
 * @return：返回值是复制到缓冲区的字符数，不包括空终止字符，否则返回默认值（缺省为0）
 **/
UINT CIniFileEdit::GetProfileInt(CfgIntStruct* pCfg, INT nDefault)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::GetPrivateProfileInt(pCfg->lpAppName, pCfg->lpKeyName, nDefault, fileName);
}

/*
 * @brief：删除顶层节点键值
 * @param：
 *      lpAppName：节点键值名称
 *      lpFileName：配置文件路径，缺省为NULL，使用m_pCfgFile的值
 * @return：成功返回TRUE，否则返回FALSE
 **/
BOOL CIniFileEdit::RemoveProfileKey(LPCTSTR lpAppName, LPCTSTR lpFileName)
{
    if (NULL == lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != lpFileName)
        fileName = lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(lpAppName, NULL , NULL, fileName);
}

/*
 * @brief：删除子键值
 * @param：
 *      lpAppName：节点键值名称
 *      lpKeyName：子键值名称
 *      lpFileName：配置文件路径，缺省为NULL，使用m_pCfgFile的值
 * @return：成功返回TRUE，否则返回FALSE
 **/
BOOL CIniFileEdit::RemoveProfileSubKey(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName)
{
    if (NULL == lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != lpFileName)
        fileName = lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(lpAppName, lpKeyName, NULL, fileName);
}
