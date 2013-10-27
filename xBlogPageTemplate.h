/*
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012-2013, xSky <guozhw at gmail dot com>
 * All rights reserved.
 * Distributed under GPL license.
 * ----------------------------------------------------------------------------
 */
 
#include <string>
#include <map>

#include "xBlogBase.h"
#include "xConfig.h"
#include "xBlogData.h"
#include "xLog.h"
#include "xConfig.h"

using namespace std;

class xBlogPageTemplate;
typedef string(xBlogPageTemplate::*TEMPLATECB) (string & html);

struct XTEMPLATE
{
	string value;
	TEMPLATECB templateCB;
};

class xBlogPageTemplate
{
public:
	xBlogPageTemplate(){}
	~xBlogPageTemplate(){}

	static xBlogPageTemplate *GetInstance();
	static xBlogPageTemplate *gXBlogPageTemplate;

public:
	void Init();
	bool BuildHtmlByTemplateKey(const char *pKey, XTEMPLATE & strHtml);

	string GetPageTemplate(const char *pKey)
	{
		return PageTemplateMap[pKey].value;
	}
	string GetActiveTemplate(const char *pKey)
	{
		return ActiveTemplateMap[pKey].value;
	}
	string GetPageCache(const char *pKey)
	{
		return PageCacheMap[pKey].value;
	}

private:
	XTEMPLATE & GetFile(string filedir, string filename,
		XTEMPLATE & xtemplate, TEMPLATECB xCall = NULL);

	void LoadTemplatePage();
	void LoadCachePage();
	void LoadCachePageData();

    string GetCacheIncludeCatalog(string & strHtml);
    string GetCacheIncludeLink(string & strHtml);
    
	void ReplacePageTemplate(string & strHtml);
	void ReplaceSiteConfig(string & strHtml);
	void ReplacePageCache(string & strHtml);
	

private:
	map < string, XTEMPLATE > PageTemplateMap;
	map < string, XTEMPLATE > ActiveTemplateMap;
	map < string, XTEMPLATE > PageCacheMap;
};