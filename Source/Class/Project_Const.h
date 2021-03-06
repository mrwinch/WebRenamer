﻿//---------------------------------------------------------------------------
#include "SysLogger.h"
#include "NameValue.h"
#include "ConnectionManager.h"
#include "ExtStringList.h"
#include "NameTranslator.h"
#include "MyHTMLParser.h"
//---------------------------------------------------------------------------
#ifndef Project_ConstH
#define Project_ConstH
#define WEB_RENAMER_DEBUG                           1
//---------------------------------------------------------------------------
#define START_PARAMETER             				"<<"
#define END_PARAMETER                               ">>"
#define AS_PARAMETER(Value)                         (String)START_PARAMETER+Value+(String)END_PARAMETER
#define START_CLIENT_PARAMETER                      "%#"
#define END_CLIENT_PARAMETER                        "#%"
#define CLIENT_PARAMETER_SEPARATOR                  "|"
#define LANGUAGE_IDENTIFIER_PARAMETER               "Preflanguage"
#define CANDIDATE_STRING_ID                         START_PARAMETER+(String)"candidate"+END_PARAMETER
#define SHOW_STRING_ID                              START_PARAMETER+(String)"tv_id"+END_PARAMETER
#define SHOW_SEASON_STRING_ID                       START_PARAMETER+(String)"season_id"+END_PARAMETER
#define SHOW_EPISODE_STRING_ID                      START_PARAMETER+(String)"episode_id"+END_PARAMETER

#define CONFIGURATION_FILE                          "WebRenamer.cfg"
#define DEBUG_FILE                                  "Debug.log"

#define APP_VERSION                                 0x01
#define APP_SUBVERSION                              0x00
#define APP_BUILD                                   0x01
#define APP_NAME                                    "WebRenamer"
//---------------------------------------------------------------------------
#define NO_DEBUG                                    0x00		//No debug
#define ERR_DEBUG                                   0x01		//Error 
#define WARN_DEBUG                                  0x02		//Warning
#define INFO_DEBUG                                  0x03		//Execution of function
#define TOTAL_DEBUG                                 0x04		//Details about execution
#define NAME_LEVEL(Level)	(Level == ERR_DEBUG?"ERRO":(Level == WARN_DEBUG?"WARN":(Level == INFO_DEBUG?"INFO":(Level == TOTAL_DEBUG?"TOTL":"UNKL"))))
#define QUOTED(Obj)									(String)"'"+Obj->Name+(String)"'"
#define QUOTE_STRING(Str)							(String)"'"+Str+(String)"'"
//---------------------------------------------------------------------------
#define ISO_639_LEN                                 185
//---------------------------------------------------------------------------
#define DIALOG_OK				(System::Set<System::Uitypes::TMsgDlgBtn, _DELPHI_SET_ENUMERATOR(System::Uitypes::TMsgDlgBtn::mbYes), _DELPHI_SET_ENUMERATOR(System::Uitypes::TMsgDlgBtn::mbClose)>() << System::Uitypes::TMsgDlgBtn::mbOK )
#define DIALOG_OK_ABORT			(System::Set<System::Uitypes::TMsgDlgBtn, _DELPHI_SET_ENUMERATOR(System::Uitypes::TMsgDlgBtn::mbYes), _DELPHI_SET_ENUMERATOR(System::Uitypes::TMsgDlgBtn::mbClose)>() << System::Uitypes::TMsgDlgBtn::mbOK << System::Uitypes::TMsgDlgBtn::mbAbort )
//TSysLog *Logger;
//int ReqCreated = 0;
//---------------------------------------------------------------------------
typedef struct{
	int ID;
	String Abbreviation;
	String Name;
	String EnglishName;
}PreferedLanguage;
const PreferedLanguage Language639[] = {
	{102,"ab","аҧсуа бызшәа","Abkhaz"},
	{101,"aa","Afaraf","Afar"},
	{103,"af","Afrikaans","Afrikaans"},
	{104,"ak","Akan","Akan"},
	{230,"sq","gjuha shqipe","Albanian"},
	{105,"am","አማርኛ","Amharic"},
	{106,"ar","العربية","Arabic"},
	{107,"an","aragonés","Aragonese"},
	{154,"hy","Հայերեն","Armenian"},
	{108,"as","অসমীয়া","Assamese"},
	{109,"av","авар мацӀ","Avaric"},
	{110,"ae","avesta","Avestan"},
	{111,"ay","aymar aru","Aymara"},
	{112,"az","azərbaycan dili","Azerbaijani"},
	{114,"bm","bamanankan","Bambara"},
	{113,"ba","башҡорт теле","Bashkir"},
	{136,"eu","euskara","Basque"},
	{115,"be","беларуская мова","Belarusian"},
	{116,"bn","বাংলা","Bengali"},
	{117,"bh","भोजपुरी","Bihari"},
	{118,"bi","Bislama","Bislama"},
	{120,"bs","bosanski jezik","Bosnian"},
	{121,"br","brezhoneg","Breton"},
	{122,"bg","български език","Bulgarian"},
	{197,"my","Burmese","Burmese"},
	{123,"ca","català","Catalan"},
	{124,"ch","Chamoru","Chamorro"},
	{125,"ce","нохчийн мотт","Chechen"},
	{206,"ny","chiCheŵa","Chichewa"},
	{27,"zh","中文","Chinese"},
	{127,"cv","чӑваш чӗлхи","Chuvash"},
	{128,"kw","Kernewek","Cornish"},
	{129,"co","corsu","Corsican"},
	{130,"cr","ᓀᐦᐃᔭᐍᐏᐣ","Cree"},
	{31,"hr","hrvatski jezik","Croatian"},
	{28,"cs","čeština","Czech"},
	{10,"da","dansk","Danish"},
	{132,"dv","ދިވެހި","Divehi"},
	{13,"nl","Nederlands","Dutch"},
	{133,"dz","རྫོང་ཁ","Dzongkha"},
	{7,"en","English","English"},
	{134,"eo","Esperanto","Esperanto"},
	{135,"et","eesti","Estonian"},
	{137,"ee","Eʋegbe","Ewe"},
	{138,"fo","føroyskt","Faroese"},
	{140,"fj","vosa Vakaviti","Fijian"},
	{11,"fi","suomi","Finnish"},
	{17,"fr","français","French"},
	{142,"ff","Fulfulde","Fula"},
	{145,"gl","galego","Galician"},
	{168,"ka","ქართული","Georgian"},
	{14,"de","Deutsch","German"},
	{20,"el","ελληνική γλώσσα","Greek"},
	{147,"gn","Avañe'ẽ","Guaraní"},
	{148,"gu","ગુજરાતી","Gujarati"},
	{149,"ht","Kreyòl ayisyen","Haitian"},
	{150,"ha","هَوُسَ","Hausa"},
	{24,"he","עברית","Hebrew"},
	{151,"hz","Otjiherero","Herero"},
	{152,"hi","हिन्दी","Hindi"},
	{153,"ho","Hiri Motu","Hiri Motu"},
	{19,"hu","Magyar","Hungarian"},
	{163,"is","Íslenska","Icelandic"},
	{156,"io","Ido","Ido"},
	{155,"ig","Asụsụ Igbo","Igbo"},
	{161,"id","Bahasa Indonesia","Indonesian"},
	{160,"ia","Interlingua","Interlingua"},
	{159,"ie","Interlingue","Interlingue"},
	{158,"iu","ᐃᓄᒃᑎᑐᑦ","Inuktitut"},
	{162,"ik","Iñupiaq","Inupiaq"},
	{144,"ga","Gaeilge","Irish"},
	{15,"it","italiano","Italian"},
	{25,"ja","日本語","Japanese"},
	{164,"jv","basa Jawa","Javanese"},
	{165,"kl","kalaallisut","Kalaallisut"},
	{166,"kn","ಕನ್ನಡ","Kannada"},
	{169,"kr","Kanuri","Kanuri"},
	{167,"ks","कश्मीरी","Kashmiri"},
	{170,"kk","қазақ тілі","Kazakh"},
	{171,"km","ខ្មែរ","Khmer"},
	{172,"ki","Gĩkũyũ","Kikuyu"},
	{173,"rw","Ikinyarwanda","Kinyarwanda"},
	{174,"ky","кыргыз тили","Kirghiz"},
	{219,"rn","Ikirundi","Kirundi"},
	{175,"kv","коми кыв","Komi"},
	{176,"kg","KiKongo","Kongo"},
	{32,"ko","한국어","Korean"},
	{178,"ku","Kurdî","Kurdish"},
	{177,"kj","Kuanyama","Kwanyama"},
	{179,"lo","ພາສາລາວ","Lao"},
	{180,"la","latine","Latin"},
	{181,"lv","latviešu valoda","Latvian"},
	{182,"li","Limburgs","Limburgish"},
	{183,"ln","Lingála","Lingala"},
	{184,"lt","lietuvių kalba","Lithuanian"},
	{186,"lu","Luba-Katanga","Luba-Katanga"},
	{187,"lg","Luganda","Luganda"},
	{185,"lb","Lëtzebuergesch","Luxembourgish"},
	{191,"mk","македонски јазик","Macedonian"},
	{192,"mg","Malagasy fiteny","Malagasy"},
	{196,"ms","bahasa Melayu","Malay"},
	{189,"ml","മലയാളം","Malayalam"},
	{193,"mt","Malti","Maltese"},
	{146,"gv","Gaelg","Manx"},
	{195,"mi","te reo Māori","Māori"},
	{190,"mr","मराठी","Marathi"},
	{188,"mh","Kajin M̧ajeļ","Marshallese"},
	{194,"mn","монгол","Mongolian"},
	{198,"na","Ekakairũ Naoero","Nauru"},
	{199,"nv","Diné bizaad","Navajo"},
	{202,"ng","Owambo","Ndonga"},
	{203,"ne","नेपाली","Nepali"},
	{201,"nd","isiNdebele","North Ndebele"},
	{224,"se","Davvisámegiella","Northern Sami"},
	{9,"no","Norsk","Norwegian"},
	{205,"nb","Norsk bokmål","Norwegian Bokmål"},
	{204,"nn","Norsk nynorsk","Norwegian Nynorsk"},
	{157,"ii","Nuosuhxop","Nuosu"},
	{207,"oc","occitan","Occitan"},
	{208,"oj","ᐊᓂᔑᓈᐯᒧᐎᓐ","Ojibwe"},
	{126,"cu","ѩзыкъ словѣньскъ","Old Church Slavonic"},
	{209,"or","ଓଡ଼ିଆ","Oriya"},
	{210,"om","Afaan Oromoo","Oromo"},
	{211,"os","ирон æвзаг","Ossetian"},
	{213,"pi","पाऴि","Pāli"},
	{212,"pa","ਪੰਜਾਬੀ","Panjabi"},
	{215,"ps","پښتو","Pashto"},
	{139,"fa","فارسی","Persian"},
	{18,"pl","język polski","Polish"},
	{214,"pt","português","Portuguese"},
	{26,"pt","português - Brazil","Portuguese - Brazil"},
	{216,"qu","Runa Simi","Quechua"},
	{218,"ro","limba română","Romanian"},
	{217,"rm","rumantsch grischun","Romansh"},
	{22,"ru","русский язык","Russian"},
	{225,"sm","gagana fa'a Samoa","Samoan"},
	{220,"sg","yângâ tî sängö","Sango"},
	{221,"sa","संस्कृतम्","Sanskrit"},
	{231,"sc","sardu","Sardinian"},
	{143,"gd","Gàidhlig","Scottish Gaelic"},
	{232,"sr","српски језик","Serbian"},
	{226,"sn","chiShona","Shona"},
	{227,"sd","सिन्धी","Sindhi"},
	{222,"si","සිංහල","Sinhala"},
	{30,"sk","slovenčina","Slovak"},
	{223,"sl","slovenski jezik","Slovene"},
	{228,"so","Soomaaliga","Somali"},
	{200,"nr","isiNdebele","South Ndebele"},
	{229,"st","Sesotho","Southern Sotho"},
	{16,"es","español","Spanish"},
	{234,"su","Basa Sunda","Sundanese"},
	{235,"sw","Kiswahili","Swahili"},
	{233,"ss","SiSwati","Swati"},
	{8,"sv","svenska","Swedish"},
	{241,"tl","Wikang Tagalog","Tagalog"},
	{236,"ty","Reo Tahiti","Tahitian"},
	{240,"tg","тоҷикӣ","Tajik"},
	{237,"ta","தமிழ்","Tamil"},
	{238,"tt","татар теле","Tatar"},
	{239,"te","తెలుగు","Telugu"},
	{242,"th","ไทย","Thai"},
	{119,"bo","བོད་ཡིག","Tibetan Standard"},
	{243,"ti","ትግርኛ","Tigrinya"},
	{244,"to","faka Tonga","Tonga"},
	{246,"ts","Xitsonga","Tsonga"},
	{245,"tn","Setswana","Tswana"},
	{21,"tr","Türkçe","Turkish"},
	{247,"tk","Türkmen","Turkmen"},
	{248,"tw","Twi","Twi"},
	{249,"ug","Uyƣurqə","Uighur"},
	{250,"uk","українська мова","Ukrainian"},
	{251,"ur","اردو","Urdu"},
	{252,"uz","Ozbek","Uzbek"},
	{253,"ve","Tshivenḓa","Venda"},
	{254,"vi","Tiếng Việt","Vietnamese"},
	{255,"vo","Volapük","Volapük"},
	{256,"wa","walon","Walloon"},
	{131,"cy","Cymraeg","Welsh"},
	{141,"fy","Frysk","Western Frisian"},
	{257,"wo","Wollof","Wolof"},
	{258,"xh","isiXhosa","Xhosa"},
	{259,"yi","ייִדיש","Yiddish"},
	{260,"yo","Yorùbá","Yoruba"},
	{261,"za","Saɯ cueŋƅ","Zhuang"},
	{262,"zu","isiZulu","Zulu"}
};
//---------------------------------------------------------------------------
#endif
