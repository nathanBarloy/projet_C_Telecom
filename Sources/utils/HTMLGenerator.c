#include "HTMLGenerator.h"
#include <stdlib.h>
#include "FileToString.h"
#include <stdio.h>
#include "JSONShortcut.h"
#include "Headers.h"
#include <Vector/Vector.h>
#include "Replace.h"
#include <unistd.h>
String_t HTMLFromJSONContainer(Connexion_t connexion, JSONObject_t json, JSONObject_t container, Vector_t params)
{
	String_t html = newString();
	if(container != 0)
	{
		JSONObject_t obj = 0, detail = 0;
		bool isTag = true;
		obj = container;
		if(JSONObject_getType(obj) == OBJECT)
		{
			printf("JSONContainer:\n%s\n", cString(JSONObject_asString(container, 0)));
			detail = JSONObject_get(obj, AS("tag"));
			isTag = 0;
			if(detail == 0)
			{
				detail = JSONObject_get(obj, AS("file"));
				isTag = 1;
			}
			if(detail == 0)
			{
				detail = JSONObject_get(obj, AS("function"));
				isTag = 2;
			}
			if(detail != 0)
			{
				if(JSONObject_getType(detail) == OBJECT)
				{
					//Verification des droits
					bool displayed = true;
					if(JSONObject_get(detail, AS("ifconnected")) != 0)
					{
						//printf("Test ifconnected:\n");
						bool rq = JSONObject_booleanValueOf(detail, AS("ifconnected"));
						bool ob = sizeOfString(connexion->addr_s) > 0 ? true : false;
						//printf("Rq: %d\nOb: %d\n", (int) rq, (int) ob);
						//printf("Value: %s\n", cString(JSONObject_stringValueOf(detail, AS("ifconnected"))));
						//printf("Detail: %s\n", cString(JSONObject_asString(detail, 0)));
						if(rq != ob)
						{
							printf("Disabled !\n");
							displayed = false;
						}
					}
					if(JSONObject_get(detail, AS("iflogged")) != 0)
					{
						bool rq = JSONObject_booleanValueOf(detail, AS("iflogged"));
						bool ob = connexion->sid == 0 ? false : true;
						if(rq != ob)
						{
							displayed = false;
						}
					}
					//Calcul
					if(displayed)
					{
						printf("Will be displayed: %s\n", cString(JSONObject_asString(detail, 0)));
						if(isTag == 0)
						{
							AutoString_t name = JSONObject_stringValueOf(detail,AS("name")), value = JSONObject_stringValueOf(detail, AS("value"));
							JSONArray_t attributes = JSONObject_get(detail, AS("attributes")), childs = JSONObject_get(detail, AS("childs"));
							String_t chv = newStringFromCharStar("<"), spc = newStringFromCharStar(" "), echv = newStringFromCharStar(">"), slash = newStringFromCharStar("/"), eq = newStringFromCharStar("="), gui = newStringFromCharStar("\"");
							concatString(html, chv);
							concatString(html, name);
							if(attributes != 0 && JSONObject_getType(attributes) == ARRAY)
							{
								size_t c = 0, size = JSONArray_size(attributes);
								JSONObject_t attr = 0;
								String_t name = 0, value = 0;
								while(c < size)
								{
									attr = JSONArray_get(attributes, c);
									if(JSONObject_getType(attr) == OBJECT)
									{
										concatString(html, spc);
										name = JSONObject_stringValueOf(attr, autoString("name"));
										concatString(html, name);
										concatString(html, eq);
										concatString(html, gui);
										value = JSONObject_stringValueOf(attr, autoString("value"));
										String_t href = newStringFromCharStar("href"), src = newStringFromCharStar("src");
										if(equalsString(name, href) || equalsString(name, src))
										{
											String_t ep = newStringFromCharStar("exec://");
											size_t c = 0, size = sizeOfString(ep);
											bool isExec = true, isHttp = true, isHttps = true, isFtp = true;
											while(c < size && c < sizeOfString(value))
											{
												if(value->str[c] != ep->str[c])
												{
													isExec = false;
												}
												++size;
											}
											fString(ep);
											c = 0;
											ep = newStringFromCharStar("http://");
											size = sizeOfString(ep);
											while(c < size && c < sizeOfString(value))
											{
												if(value->str[c] != ep->str[c])
												{
													isHttp = false;
												}
												++size;
											}
											fString(ep);

											c = 0;
											ep = newStringFromCharStar("https://");
											size = sizeOfString(ep);
											while(c < size && c < sizeOfString(value))
											{
												if(value->str[c] != ep->str[c])
												{
													isHttps = false;
												}
												++size;
											}
											fString(ep);

											c = 0;
											ep = newStringFromCharStar("ftp://");
											size = sizeOfString(ep);
											while(c < size && c < sizeOfString(value))
											{
												if(value->str[c] != ep->str[c])
												{
													isFtp = false;
												}
												++size;
											}
											fString(ep);



											if(!isExec && !isHttp && !isHttps && !isFtp)
											{
													char *wd = getcwd(0,0);
													String_t cwd = newStringFromCharStar(wd);
													free(wd);
													String_t r = newStringFromCharStar("file://");
													concatString(r, cwd);
													fString(cwd);
													cwd = newStringFromCharStar("/");
													concatString(r, cwd);
													fString(cwd);
													concatString(r, value);
													setString(value, r);
													fString(r);
											}
										}
										fString(href);
										fString(src);
										concatString(html, value);
										concatString(html, gui);
									}
									else
									{
										printf("HTMLGenerator: Error, attribute must be an object.\n");
									}
									++c;
								}
							}
							else
							{
								printf("HTMLGenerator: Error, attributes must be an array.\n");
							}
							if(childs != 0)
							{
								concatString(html, echv);
								if(JSONObject_getType(childs) == ARRAY)
								{
									size_t c = 0, size = JSONArray_size(childs);
									while(c < size)
									{
										concatString(html, HTMLFromJSONContainer(connexion, json, JSONArray_get(childs, c), params));
										++c;
									}
								}
								concatString(html, chv);
								concatString(html, slash);
								concatString(html, name);
								concatString(html, echv);
							}
							else if(value != 0)
							{
								concatString(html, echv);
								concatString(html, value);
								concatString(html, chv);
								concatString(html, slash);
								concatString(html, name);
								concatString(html, echv);
							}
							else
							{
								concatString(html, slash);
								concatString(html, echv);
							}

							//fmString(6, chv, spc, echv, slash, eq, gui);
							fString(chv);
							fString(spc);
							fString(echv);
							fString(slash);
							fString(eq);
							fString(gui);

						}
						else if(isTag == 1)
						{
							String_t tmp = fileToString(autoConcatString(autoString("web/"), JSONObject_stringValueOf(detail, AS("name"))));
							if(tmp != 0)
							{
								concatString(html, tmp);
								fString(tmp);
							}
							else
							{
								printf("HTMLGenerator: Unable to load: %s\n", cString(JSONObject_stringValueOf(detail, AS("file"))));
							}
						}
						else if(isTag == 2)
						{
							printf("Not implemented yet.\n");
						}
					}
					else
					{
						printf("Will NOT be displayed: %s\n", cString(JSONObject_asString(detail, 0)));
					}
				}
				else
				{
					printf("HTMLGenerator: Container must contains objects. (in tag or file).\n");
				}
			}
			else
			{
				printf("HTMLGenerator: Container must be a tag or a file.\n");
			}
		}
		else
		{
			printf("HTMLGenerator: Container must contains objects.\n");
		}
	}
	else
	{
		printf("HTMLGenerator: Empty container !\n");
	}
	return html;
}
int HTMLFROMJSONLastTime = 0;
String_t HTMLFromJSON(Connexion_t connexion, JSONObject_t json, Vector_t params)
{
	String_t html = 0;
	if(json != 0 && JSONObject_getType(json) == OBJECT)
	{
		printf("JSONObject:\n%s\n", cString(JSONObject_asString(json, 0)));
		html = newStringFromCharStar("<!DOCTYPE html>\n<html>\n<head>\n<title>");
		String_t tmp = 0;
		concatString(html, JSONObject_stringValueOf(json, AS("title")));
		tmp = newStringFromCharStar("</title>\n");
		concatString(html, tmp);
		fString(tmp);
		size_t c = 0, size = 0;
		{
			JSONArray_t head = JSONObject_get(json, AS("head"));
			if(head != 0 && JSONObject_getType(head) == ARRAY)
			{
				c = 0;
				size = JSONArray_size(head);
				while(c < size)
				{
					printf("HEAD: %lu/%lu\n", (c + 1), size);
					tmp = HTMLFromJSONContainer(connexion, json, JSONArray_get(head, c), params);
					concatString(html, tmp);
					fString(tmp);
					++c;
				}
			}
			else
			{
				printf("HTMLGenerator: Head is not an array.\n");
			}
		}
		{
			String_t ss = newStringFromCharStar("\n<style>\n"), es = newStringFromCharStar("\n</style>\n");
			JSONArray_t styles = JSONObject_get(json, AS("styles"));
			if(styles != 0 && JSONObject_getType(styles) == ARRAY)
			{
				c = 0;
				size = JSONArray_size(styles);
				while(c < size)
				{
					tmp = FileToString(autoConcatString(autoString("web/"), JSONArray_stringValue(styles, c)));
					if(tmp != 0)
					{
						concatString(html, ss);
						concatString(html, tmp);
						concatString(html, es);
						fString(tmp);
					}
					else
					{
						printf("HTMLGenerator: Unable to load: %s\n", cString(JSONArray_stringValue(styles, c)));
					}
					++c;
				}
			}
			else
			{
				printf("HTMLGenerator: Styles is not an array.\n");
			}
			//fmString(2, ss, es);
			fString(ss);
			fString(es);
		}
		tmp = newStringFromCharStar("</head>\n<body>\n");
		concatString(html, tmp);
		fString(tmp);
		{
			JSONArray_t body = JSONObject_get(json, AS("body"));
			if(body != 0 && JSONObject_getType(body) == ARRAY)
			{
				c = 0;
				size = JSONArray_size(body);
				while(c < size)
				{
					printf("BODY: %lu/%lu\n", (c + 1), size);
					tmp = HTMLFromJSONContainer(connexion, json, JSONArray_get(body, c), params);
					concatString(html, tmp);
					fString(tmp);
					++c;
				}
			}
			else
			{
				printf("HTMLGenerator: Body is not an array.\n");
			}
		}
		{
			String_t ss = newStringFromCharStar("\n<script>\n"), es = newStringFromCharStar("\n</script>\n");
			JSONArray_t scripts = JSONObject_get(json, AS("scripts"));
			if(scripts != 0 && JSONObject_getType(scripts) == ARRAY)
			{
				c = 0;
				size = JSONArray_size(scripts);
				while(c < size)
				{
					tmp = FileToString(autoConcatString(autoString("web/"), JSONArray_stringValue(scripts, c)));
					if(tmp != 0)
					{
						concatString(html, ss);
						concatString(html, tmp);
						concatString(html, es);
						fString(tmp);
					}
					else
					{
						printf("HTMLGenerator: Unable to load: %s\n", cString(JSONArray_stringValue(scripts, c)));
					}
					++c;
				}
			}
			else
			{
				printf("HTMLGenerator: Scripts is not an array.\n");
			}
			//fmString(2, ss, es);
			fString(ss);
			fString(es);
		}
		tmp = newStringFromCharStar("</body>\n</html>");
		concatString(html, tmp);
		fString(tmp);
	}
	else
	{
		html = newStringFromCharStar("<!DOCTYPE html>\n<html><head></head><body></body></html>");
		printf("HTMLGenerator: No JSON object received.\n");
		if(HTMLFROMJSONLastTime == 0)
		{
			HTMLFROMJSONLastTime = 1;
			String_t html2 = HTMLFromJSONUrl(connexion, autoString("exec://error.json"));
			HTMLFROMJSONLastTime = 0;
			if(html2 != 0)
			{
				fString(html);
				html = html2;
			}
		}
	}
	return html;
}
String_t HTMLFromJSONString(Connexion_t connexion, String_t str, Vector_t params)
{
	return HTMLFromJSON(connexion, JSONParser_parseString(str), params);
}
String_t HTMLFromJSONFile(Connexion_t connexion, String_t file, Vector_t params)
{
	return HTMLFromJSON(connexion, JSONParser_parseFileString(file), params);
}
String_t HTMLFromJSONUrl(Connexion_t connexion, String_t url)
{
	if(sizeOfString(url) >= sizeOfString(autoString(("exec://"))))
	{
		String_t file = newStringFromCharStar(url->str + sizeOfString(autoString("exec://")));
		Vector_t params = newVector();
		int pos = getFirstChar(file, '?');
		if(pos > -1)
		{
			String_t p = cutString(file, pos), tmp = 0;
			printf("File: %s\nParams: %s\n", cString(file), cString(p));
			tmp = cutString(p, 1);
			fString(p);
			p = tmp;
			pos = getFirstChar(p, '=');
			bool last = false;
			while(pos > - 1)
			{
				tmp = cutString(p, pos);
				String_t name = p;
				if(tmp == 0)
				{
					//printf("#1\n");
					p = name;
					break;
				}
				p = tmp;
				if(sizeOfString(p) == 0)
				{
					//printf("#2\n");
					break;
				}
				tmp = cutString(p, 1);
				fString(p);
				p = tmp;
				//Obtenir le & au bon endroit
				pos = getFirstChar(p, '&');
				if(pos == -1 || sizeOfString(p) == 0)
				{
					/*printf("#3\n");
					break;*/
					last = true;
				}
				else
				{
					tmp = cutString(p, pos);
				}
				String_t value = p;
				transformValue(value);
				Header_t h = newHeaderFull(cString(name), cString(value));
				printf("Couple: %s - %s\n", cString(name), cString(value));
				//fString(name);
				//fString(value);
				addToVector(params, (void*) h);
				p = tmp;
				if(sizeOfString(p) == 0)
				{
					//printf("#4\n");
					break;
				}
				if(last)
				{
					break;
				}
				tmp = cutString(p, 1);
				fString(p);
				p = tmp;
				if(sizeOfString(p) == 0)
				{
					//printf("#5\n");
					break;
				}
				pos = getFirstChar(p, '=');
			}
			fString(p);
		}
		String_t r = HTMLFromJSONFile(connexion, autoConcatString(autoString("web/"), file), params);
		params = freeVectorWithPtr(params, freeHeaderPtr);
		fString(file);
		return r;
	}
	return 0;
}
