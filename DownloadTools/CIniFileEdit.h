#pragma once

/* INI本地配置文件解析类 */
class CIniFileEdit
{
	LPCTSTR m_pCfgFile; // INI配置文件路径

public:
	typedef struct 
	{
		LPCTSTR lpAppName;  // INI文件中的一个字段名.
		LPCTSTR lpKeyName;  // lpAppName下的一个键名,通俗讲就是变量名.
		LPCTSTR lpString;   // 键值, 也就是变量的值,不过必须为LPCTSTR型或CString型的.
		LPCTSTR lpFileName; // 配置文件路径
	} CfgStrStruct;

	typedef struct
	{
		LPCTSTR lpAppName;  // INI文件中的一个字段名.
		LPCTSTR lpKeyName;  // lpAppName下的一个键名,通俗讲就是变量名.
		INT nDefault;       // 键值, 也就是变量的值,不过必须为LPCTSTR型或CString型的.
		LPCTSTR lpFileName; // 配置文件路径
	} CfgIntStruct;

public:
	// 构造与析构函数
	CIniFileEdit(LPCTSTR file=NULL);
	virtual ~CIniFileEdit();

	// 初始化文件/获取文件路径，把路径首地址值作为一个句柄存储到m_pCfgFile
	void SetFileHandle(LPCTSTR handle);
	LPCTSTR GetFileHandle(void);

	// 字符串类型键值操作
	DWORD GetProfileString(CfgStrStruct *pCfg, CString &nReturn); // 读取键值
	BOOL SetProfileString(CfgStrStruct *pCfg); // 写入键值

	// 数值类型键值操作
	UINT GetProfileInt(CfgIntStruct* pCfg, INT nDefault=0); // 读取键值

	// 删除键操作
	BOOL RemoveProfileKey(LPCTSTR lpAppName, LPCTSTR lpFileName = NULL); // 删除节点
	BOOL RemoveProfileSubKey(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName = NULL); // 删除键值

};

