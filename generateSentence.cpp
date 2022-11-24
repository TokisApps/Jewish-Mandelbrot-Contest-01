extern "C" { long long _rand(); }
extern "C" { void _srand(); }
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

enum Kasus {Nominativ,Akkusativ,Genitiv};
enum Numerus {Singular,Plural};
enum Genus {Maskulinum,Femininum,Neutrum};
enum Person {First,Second,Third};
enum Tempus {Past,Present,Future};


inline Kasus randKasus() {
	switch((long long)_rand() % 3) {
		case 0: return Nominativ;
		case 1: return Akkusativ;
		case 2: return Genitiv;
	}
}

inline Numerus randNumerus() {
	switch((long long)_rand() % 2) {
		case 0: return Singular;
		case 1: return Plural;
	}
}

inline Genus randGenus() {
	switch((long long)_rand() % 3) {
		case 0: return Maskulinum;
		case 1: return Femininum;
		case 2: return Neutrum;
	}
}

inline Person randPerson() {
	switch((long long)_rand() % 3) {
		case 0: return First;
		case 1: return Second;
		case 2: return Third;
	}
}

inline Tempus randTempus() {
	switch((long long)_rand() % 3) {
		case 0: return Past;
		case 1: return Present;
		case 2: return Future;
	}
}


struct KNG {
	Kasus kasus;
	Numerus numerus;
	Genus genus;

	KNG() {
		kasus = randKasus();
		numerus = randNumerus();
		genus = randGenus();
	}
};


struct TNP {
	Tempus tempus;
	Numerus numerus;
	Person person;

	TNP() {
		tempus = randTempus();
		numerus = randNumerus();
		person = randPerson();
	}

	TNP(Tempus t,Numerus n,Person p) {
		tempus = t;
		numerus = n;
		person = p;
	}
};


struct Verb {
	string verb;
	string hilfsverb;

	Verb(string a,string b) {
		hilfsverb = a;
		verb = b;
	}
};




inline string hilfsverb(const TNP tnp,string hv) {
	switch(tnp.tempus) {
		case Past:
			switch(tnp.numerus) {
				case Singular:
					switch(tnp.person) {
						case First: return hv == "ist" ? "bin" : "habe";
						case Second: return hv == "ist" ? "bist" : "hast";
						case Third: return hv == "ist" ? "ist" : "hat";
					}
				case Plural:
					switch(tnp.person) {
						case First: return hv == "ist" ? "sind" : "haben";
						case Second: return hv == "ist" ? "seid" : "habt";
						case Third: return hv == "ist" ? "sind" : "haben";
					}
			}
		case Present:
			return hv;
		case Future:
			switch(tnp.numerus) {
				case Singular:
					switch(tnp.person) {
						case First: return "werde";
						case Second: return "wirst";
						case Third: return "wird";
					}
				case Plural:
					switch(tnp.person) {
						case First: return "werden";
						case Second: return "werdet";
						case Third: return "werden";
					}
			}
	}
}




inline Verb verb(const TNP tnp) {
	const char *xs[] = {
		/*"geh","ging","ist","gegangen",
		"lauf","lief","ist","geloffen",
		"spring","sprang","ist","gesprungen",
		"heb","hob","hat","gehoben",
		"stech","stach","hat","gestochen",*/
		"back",
		"fahr",
		"grab",
		"lad",
		"schaff",
		"schlag",
		"trag",
		"wachs",
		"wasch",
		"blas",
		"brat",
		"fall",
		"halt",
		"lass",
		"rat",
		"schlaf",
		"empfang",
		"empfang",
		"fang",
		"les",
		"seh",
		"befehl",
		"befohl",
		"empfehl",
		"empfohl",
		"stehl",
		"ess",
		"fress",
		"mess",
		"tret",
		"vergess",
		"vergess",
		"berg",
		"berst",
		"brech",
		"erschreck",
		"erschrock",
		"helf",
		"nehm",
		"schelt",
		"sprech",
		"stech",
		"sterb",
		"treff",
		"verderb",
		"verdorb",
		"werb",
		"werf",
		"beweg",
		"bewog",
		"dresch",
		"fecht",
		"flecht",
		"heb",
		"melk",
		"pfleg",
		"quell",
		"scher",
		"schmelz",
		"schwell",
		"web",
		"steh",
		"bieg",
		"biet",
		"flieg",
		"flieh",
		"flie√ü",
		"frier",
		"gie√ü",
		"kriech",
		"riech",
		"schieb",
		"schie√ü",
		"schlie√ü",
		"sied",
		"sprie√ü",
		"stieb",
		"trief",
		"verdrie√ü",
		"verdross",
		"verlier",
		"verlor",
		"wieg",
		"zieh",
		"lieg",
		"beginn",
		"begonn",
		"schwimm",
		"rinn",
		"sinn",
		"spinn",
		"glimm",
		"klimm",
		"bind",
		"ding",
		"dring",
		"find",
		"kling",
		"ring",
		"schling",
		"schwind",
		"schwing",
		"sing",
		"sink",
		"spring",
		"stink",
		"trink",
		"wind",
		"wring",
		"zwing",
		"bitt",
		"sitz",
		"schind",
		"bleib",
		"leih",
		"meid",
		"preis",
		"reib",
		"scheid",
		"schein",
		"schi",
		"schreib",
		"schrei",
		"schweig",
		"spei",
		"steig",
		"treib",
		"weis",
		"verzeih",
		"verzieh",
		"bei√ü",
		"bleich",
		"gleich",
		"gleit",
		"greif",
		"kneif",
		"leid",
		"pfeif",
		"rei√ü",
		"reit",
		"schei√ü",
		"schleich",
		"schleif",
		"schmei√ü",
		"schneid",
		"schreit",
		"streich",
		"streit",
		"weich",
		"hei√ü",
		"sauf",
		"saug",
		"schnaub",
		"hau",
		"lauf",
		"komm",
		"sto√ü",
		"ruf",
		"h√§ng",
		"erl√∂sch",
		"erlosch",
		"schw√∂r",
		"l√ºg",
		"tr√ºg",
		"mahl",
		"salz",
		"spalt",
		"wiss",
		"brenn",
		"bring",
		"denk",
		"kenn",
		"nenn",
		"renn",
		"send",
		"wend",
		"hab",
		"werd",
		"k√∂nn",
		"m√∂g",
		"d√ºrf",
		"m√ºss",
		"soll",
		"woll"
		};

	const char **r = xs + ((long long)sizeof(xs) * (long long)_rand() / (long long)sizeof(*xs) / (long long)RAND_MAX);

	switch(tnp.tempus) {
		case Past:
			return Verb(hilfsverb(tnp,"hat"),string("ge") + string(r[0]) + "t");
		case Present:
			switch(tnp.numerus) {
				case Singular:
					switch(tnp.person) {
						case First: return Verb(string(r[0]) + "e","");
						case Second: return Verb(string(r[0]) + "st","");
						case Third: return Verb(string(r[0]) + "t","");
					}
				case Plural:
					switch(tnp.person) {
						case First: return Verb(string(r[0]) + "en","");
						case Second: return Verb(string(r[0]) + "t","");
						case Third: return Verb(string(r[0]) + "en","");
					}
			}
		case Future:
			return Verb(hilfsverb(tnp,"hat"),string(r[0]) + "en");
	}
}



inline string article(bool direct,KNG kng, TNP tnp) {
	switch(tnp.person) {
		case First : 
			if(!direct) {
				switch(kng.kasus) {
					case Nominativ : 
						switch(kng.numerus) {
							case Singular: return "ich";
							case Plural: return "wir";
						}
					case Akkusativ : 
						switch(kng.numerus) {
							case Singular: return "mich";
							case Plural: return "uns";
						}
					case Genitiv : 
						switch(kng.numerus) {
							case Singular: 
								switch(kng.genus) {
									case Maskulinum:return "meines";
									case Femininum:return "meiner";
									case Neutrum:return "meines";
								}
							case Plural: 
								switch(kng.genus) {
									case Maskulinum:return "unseres";
									case Femininum:return "unserer";
									case Neutrum:return "unseres";
								}
						}
				}
			}
		case Second: 
			if(!direct) {
				switch(kng.kasus) {
					case Nominativ : 
						switch(kng.numerus) {
							case Singular: return "du";
							case Plural: return "ihr";
						}
					case Akkusativ : 
						if((long long)_rand() % 2) {
							switch(kng.numerus) {
								case Singular: 
									switch(kng.genus) {
										case Maskulinum:return "deinen";
										case Femininum:return "deine";
										case Neutrum:return "dein";
									}
								case Plural: 
									switch(kng.genus) {
										case Maskulinum:return "deine";
										case Femininum:return "deine";
										case Neutrum:return "dein";
									}
							}
						} else {
							switch(kng.numerus) {
								case Singular: 
									switch(kng.genus) {
										case Maskulinum:return "euren";
										case Femininum:return "eure";
										case Neutrum:return "euer";
									}
								case Plural: 
									switch(kng.genus) {
										case Maskulinum:return "eure";
										case Femininum:return "eure";
										case Neutrum:return "eure";
									}
							}
						}
					case Genitiv : 
						if((long long)_rand() % 2) {
							switch(kng.numerus) {
								case Singular:
									switch(kng.genus) {
											 case Maskulinum: return "eures";
											 case Femininum: return "eurer";
											 case Neutrum: return "eures";
										}
								case Plural: 
									switch(kng.genus) {
										case Maskulinum:return "eurer";
										case Femininum:return "eurer";
										case Neutrum:return "eurer";
									}
							}
						} else {
							switch(kng.numerus) {
								case Singular:
									switch(kng.genus) {
											 case Maskulinum: return "deines";
											 case Femininum: return "deiner";
											 case Neutrum: return "deines";
									}
								case Plural: 
									switch(kng.genus) {
										case Maskulinum:return "deiner";
										case Femininum:return "deiner";
										case Neutrum:return "deiner";
									}
								
							}
						}
				}
			}
		case Third: 
			if(direct) {
			     switch(kng.kasus) {
				     case Nominativ :
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "der";
								     case Femininum: return "die";
								     case Neutrum: return "das";
							     }
						     case Plural:
							     return "die";
					     }
				     case Akkusativ:
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "den";
								     case Femininum: return "die";
								     case Neutrum: return "das";
							     }
						     case Plural:
						     	return "die";
					     }
				     case Genitiv:
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "des";
								     case Femininum: return "der";
								     case Neutrum: return "des";
							     }
						     case Plural:
							     return "der";
					     }
			     }
			} else {
			     switch(kng.kasus) {
				     case Nominativ :
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "ein";
								     case Femininum: return "eine";
								     case Neutrum: return "ein";
							     }
						     case Plural:
							     return "mehrere";
					     }
				     case Akkusativ:
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "ein";
								     case Femininum: return "eine";
								     case Neutrum: return "ein";
							     }
						     case Plural:
						     	return "mehrere";
					     }
				     case Genitiv:
					     switch(kng.numerus) {
						     case Singular:
							     switch(kng.genus) {
								     case Maskulinum: return "eines";
								     case Femininum: return "einer";
								     case Neutrum: return "eines";
							     }
						     case Plural:
							     return "mehrerer";
					     }
			     }
			}
	}
}



inline string adjective(bool direct,KNG kng) {
	const char *xs[] = {
		"abstinent",
		"achtsam",
		"afrikanisch",
		"akkurat",
		"alkoholisch",
		"alphabetisch",
		"√§ngstlich",
		"√§rgerlich",
		"baff",
		"bairisch",
		"bang",
		"bankrott",
		"bedrohlich",
		"beg√ºnstigt",
		"behaglich",
		"beharrlich",
		"blind",
		"brillant",
		"charmant",
		"chemisch",
		"chorisch",
		"christlich",
		"chronisch",
		"chronologisch",
		"d√§mlich",
		"d√§mmrig",
		"dankbar",
		"darstellbar",
		"dazugeh√∂rig",
		"deckend",
		"demokratisch",
		"depressiv",
		"derb",
		"dialogisch",
		"diebisch",
		"dumm",
		"dringend",
		"eckig",
		"edel",
		"effizient",
		"egoistisch",
		"ehebrecherisch",
		"ehrerbietig",
		"ehrf√ºrchtig",
		"ehrgeizig",
		"ehrlos",
		"eigenst√§ndig",
		"einladend",
		"elektrisch",
		"fabelhaft",
		"fachkundig",
		"fad", 
		"fadenscheinig",
		"fahrl√§ssig",
		"faktisch",
		"fantasielos",
		"fantastisch",
		"fein",
		"fest",
		"fettig",
		"fit",
		"flach",
		"flauschig",
		"flott",
		"g√§ngig",
		"garstig",
		"gastfreundlich",
		"gebogen",
		"gedr√ºckt",
		"geeignet",
		"gef√§hrlich",
		"gefangen",
		"geisterhaft",
		"gelb",
		"gereizt",
		"glatt",
		"gleichberechtigt",
		"gl√ºcklich",
		"grafisch",
		"gro√ü",
		"haarig",
		"halb",
		"halsbrecherisch",
		"h√§misch",
		"handlungsf√§hig",
		"hei√ü",
		"hell",
		"herzoglich",
		"hinf√§llig",
		"hoch",
		"hoffnungsvoll",
		"h√ºndisch",
		"ideal",
		"identisch",
		"idyllisch",
		"illegal",
		"illusorisch",
		"imagin√§r",
		"imponierend",
		"individuell",
		"inhaltlich",
		"inklusiv",
		"integriert",
		"international",
		"j√§hrlich",
		"jetzig",
		"jodhaltig",
		"jordanisch",
		"j√ºdisch",
		"jugendlich",
		"jung",
		"jungfr√§ulich",
		"kahl",
		"kalorisch",
		"k√§mpferisch",
		"katholisch",
		"k√§uflich",
		"keusch",
		"kirchlich",
		"klangvoll",
		"knackig",
		"kokett",
		"kontrovers",
		"korrekt",
		"krank",
		"krumm",
		"k√ºnstlich",
		"labberig", 
		"labil",
		"lahm",
		"l√§ndlich",
		"laut",
		"lebensgro√ü",
		"legitim",
		"leicht",
		"lieb",
		"lockig",
		"lokal",
		"l√∂slich",
		"luftig",
		"m√§chtig",
		"m√§nnlich",
		"ma√üvoll",
		"materiell",
		"mehrsprachig",
		"meisterlich",
		"mental",
		"mickerig", 
		"mitleidig",
		"monatlich",
		"motorisch",
		"musikalisch",
		"mutig",
		"m√ºtterlich",
		"n√§chtlich",
		"nah",
		"n√§rrisch",
		"nass",
		"negativ",
		"neidisch",
		"neu",
		"niedrig",
		"niveaulos",
		"n√∂rdlich",
		"normal",
		"notd√ºrftig",
		"oberschlau",
		"obsolet",
		"obsz√∂n",
		"ockerfarben", 
		"√∂de", 
		"offen",
		"√∂ffentlich",
		"√∂kologisch",
		"√∂lig",
		"olympiareif",
		"operativ",
		"oral",
		"√∂rtlich",
		"√∂sterlich",
		"p√§dagogisch",
		"paradiesisch",
		"parkartig",
		"parlamentarisch",
		"passiv",
		"peinlich",
		"pensioniert",
		"pers√∂nlich",
		"perspektivlos",
		"pflichtbewusst",
		"phantastisch",
		"physisch",
		"politisch",
		"poetisch",
		"praktisch",
		"provokant",
		"qualitativ",
		"qualvoll",
		"quecksilberhaltig",
		"quengelig",
		"quergestreift",
		"quicklebendig",
		"quietschfidel",
		"rabenschwarz",
		"radikal",
		"raffiniert",
		"rankenartig",
		"rasch",
		"ratlos",
		"rauchfrei",
		"recyclebar",
		"reformbed√ºrftig",
		"regnerisch",
		"reich",
		"rein",
		"relativ",
		"respektvoll", 
		"rhythmisch",
		"riesig",
		"roh",
		"rostig",
		"r√ºckl√§ufig",
		"sachkundig",
		"sachlich",
		"saisonal",
		"salzig",
		"sauer",
		"scharf",
		"schattig",
		"schleimig",
		"schreckenerregend",
		"schusselig",
		"seidenweich",
		"selbstst√§ndig",
		"sesshaft",
		"sicher",
		"soft",
		"sperrig",
		"spitz",
		"steil",
		"stramm",
		"tailliert",
		"taktvoll",
		"technisch",
		"temperamentvoll",
		"theoretisch",
		"topografisch",
		"tot",
		"tr√§chtig",
		"traditionell",
		"treu",
		"trocken",
		"trotzig",
		"t√ºchtig",
		"√ºbel",
		"√ºbertrieben",
		"√ºberparteilich",
		"ultimativ",
		"ultrakurz",
		"umkehrbar",
		"umst√§ndlich",
		"unbehaglich",
		"unerl√§sslich",
		"uralt",
		"variabel",
		"v√§terlich",
		"verabscheuungsw√ºrdig",
		"verantwortungslos",
		"verbl√ºfft",
		"verdaulich",
		"verklemmt",
		"versichert",
		"viert√ºrig",
		"viral",
		"voll",
		"wach",
		"weise",
		"wahlberechtigt",
		"warm",
		"w√§ssrig",
		"weich",
		"weihnachtlich",
		"weit",
		"weise",
		"wei√ü",
		"weitreichend",
		"wertvoll",
		"widerlegbar",
		"wirtschaftlich",
		"wohnlich",
		"x,-beliebig",
		"x-fach",
		"y-f√∂rmig",
		"zackig",
		"zahlenm√§√üig",
		"zappelig", 
		"zart",
		"zehnj√§hrig",
		"zeitlich",
		"zentral",
		"zickig",
		"zinslos",
		"zivil",
		"zornig",
		"zuckerfrei",
		"zuvorkommend",
		"zweckgebunden",
		"zweifach",
		"zynisch"	
	};

	const char *r = xs[(long long)sizeof(xs) * (long long)_rand() / (long long)sizeof(*xs) / (long long)RAND_MAX];

	switch(kng.kasus) {
		case Nominativ:
			switch(kng.numerus) {
				case Singular:
					switch(kng.genus) {
						case Maskulinum: return string(r) + (direct ? "e" : "er");
						case Femininum: return string(r) + "e";
						case Neutrum: return string(r) + (direct ? "e" : "es");
					}
				case Plural:
					switch(kng.genus) {
						case Maskulinum: return string(r) + (direct ? "en" : "en");
						case Femininum: return string(r) + (direct ? "en" : "en");
						case Neutrum: return string(r) + (direct ? "en" : "en");
					}
			}
		case Akkusativ:
			switch(kng.numerus) {
				case Singular:
					switch(kng.genus) {
						case Maskulinum: return string(r) + "en";
						case Femininum: return string(r) + "e";
						case Neutrum: return string(r) + (direct ? "e" : "es");
					}
				case Plural:
					switch(kng.genus) {
						case Maskulinum: return string(r) + "en";
						case Femininum: return string(r) + "en";
						case Neutrum: return string(r) + (direct ? "en" : "e");
					}
			}
		case Genitiv:
			switch(kng.numerus) {
				case Singular:
					switch(kng.genus) {
						case Maskulinum: return string(r) + "en";
						case Femininum: return string(r) + "en";
						case Neutrum: return string(r) + "en";
					}
				case Plural:
					switch(kng.genus) {
						case Maskulinum: return string(r) + "en";
						case Femininum: return string(r) + "en";
						case Neutrum: return string(r) + "en";
					}
			}
	}
}


inline string noun(bool direct,KNG kng) {
	const char **xs;
	const char *as[] = {
		"√Ñrger",
		"Abend",
		"Abflug",
		"Absender",
		"Alkohol",
		"Anfang",
		"Angestellte",
		"Anruf",
		"Anrufbeantworter",
		"Anschluss",
		"Anzug",
		"Apfel",
		"Appetit",
		"April",
		"Arbeitsplatz",
		"Arm",
		"Arzt",
		"Aufenthalt",
		"Aufzug",
		"August",
		"Ausflug",
		"Ausgang",
		"Ausl√§nder",
		"Ausweis",
		"Automat",
		"Bahnhof",
		"Bahnsteig",
		"Balkon",
		"Baum",
		"Beamte",
		"Bekannte",
		"Berg",
		"Beruf",
		"Besuch",
		"Betrag",
		"Bildschirm",
		"Bleistift",
		"Blick",
		"Bogen",
		"Brief",
		"Briefkasten",
		"Briefumschlag",
		"Bruder",
		"Buchstabe",
		"Bus",
		"Chef",
		"Computer",
		"Dank",
		"Deutsche",
		"Dezember",
		"Dienstag",
		"Doktor",
		"Dom",
		"Donnerstag",
		"Drucker",
		"Durst",
		"Ehemann",
		"Eingang",
		"Eintritt",
		"Einwohner",
		"Empf√§nger",
		"Empfang",
		"Enkel",
		"Erwachsene",
		"Export",
		"F√ºhrerschein",
		"Fahrer",
		"Fahrplan",
		"Familienname",
		"Familienstand",
		"Februar",
		"Fehler",
		"Film",
		"Fisch",
		"Flughafen",
		"Flur",
		"Fluss",
		"Fotoapparat",
		"Fr√ºhling",
		"Freitag",
		"Freund",
		"Friseur",
		"Fu√ü",
		"Fu√üball",
		"Garten",
		"Gast",
		"Geburtsort",
		"Geburtstag",
		"Gl√ºckwunsch",
		"Gro√üvater",
		"Gru√ü",
		"Hals",
		"Haushalt",
		"Hausmann",
		"Herbst",
		"Herd",
		"Herr",
		"Hund",
		"Hunger",
		"Import",
		"Inhalt",
		"Januar",
		"Job",
		"Jugendliche",
		"Juli",
		"Junge",
		"Juni",
		"K√§se",
		"K√∂rper",
		"K√ºhlschrank",
		"Kaffee",
		"Kalender",
		"Kassettenrecorder",
		"Keller",
		"Kellner",
		"Kindergarten",
		"Kinderwagen",
		"Kiosk",
		"Koffer",
		"Kollege",
		"Kontakt",
		"Kopf",
		"Kredit",
		"Kreis",
		"Kuchen",
		"Kugelschreiber",
		"Kunde",
		"Kurs",
		"L√∂ffel",
		"Laden",
		"Lehrer",
		"LKW",
		"Loch",
		"Lohn",
		"M√§rz",
		"M√ºll",
		"Magen",
		"Mai",
		"Mann",
		"Mantel",
		"Markt",
		"Mechaniker",
		"Mensch",
		"Messer",
		"Mittag",
		"Mittwoch",
		"Moment",
		"Monat",
		"Montag",
		"Morgen",
		"Motor",
		"Mund",
		"Nachbar",
		"Nachmittag",
		"Name",
		"Nebel",
		"Norden",
		"Notarzt",
		"Notfall",
		"November",
		"Ober",
		"Oktober",
		"Opa",
		"Ort",
		"Osten",
		"Park",
		"Partner",
		"Pass",
		"Pkw",
		"Plan",
		"Platz",
		"Preis",
		"Prospekt",
		"Pullover",
		"R√ºcken",
		"Rabatt",
		"Raucher",
		"Raum",
		"Regen",
		"Reifen",
		"Reis",
		"Reisef√ºhrer",
		"Rock",
		"Ros√©",
		"Rundgang",
		"S√ºden",
		"Saft",
		"Salat",
		"Satz",
		"Sch√ºler",
		"Schalter",
		"Schild",
		"Schinken",
		"Schirm",
		"Schl√ºssel",
		"Schluss",
		"Schnee",
		"Schnupfen",
		"Schrank",
		"Schuh",
		"See",
		"September",
		"Service",
		"Sessel",
		"Sohn",
		"Sommer",
		"Sonntag",
		"Spa√ü",
		"Spaziergang",
		"Spielplatz",
		"Stempel",
		"Stock",
		"Stoff",
		"Strand",
		"Strom",
		"Student",
		"Stuhl",
		"Supermarkt",
		"Tag",
		"Teil",
		"Teller",
		"Teppich",
		"Termin",
		"Test",
		"Text",
		"Tipp",
		"Tisch",
		"Topf",
		"Tourist",
		"Turm",
		"Tyr",
		"Unfall",
		"Unterricht",
		"Unterschied",
		"Urlaub",
		"Vater",
		"Verein",
		"Verk√§ufer",
		"Verkehr",
		"Vermieter",
		"Vertrag",
		"Vogel",
		"Vormittag",
		"Vorname",
		"Wagen",
		"Wald",
		"Weg",
		"Wein",
		"Westen",
		"Wetter",
		"Wind",
		"Winter",
		"Wochentag",
		"Wunsch",
		"Zahn",
		"Zettel",
		"Zoll",
		"Zucker",
		"Zug",
		0
	};
	const char *bs[] = {
		"√Ñrztin",
		"√úbernachtung",
		"Abfahrt",
		"Adresse",
		"Ampel",
		"Angestellte",
		"Angst",
		"Ankunft",
		"Anmeldung",
		"Anrede",
		"Ansage",
		"Antwort",
		"Anzeige",
		"Apotheke",
		"Arbeit",
		"Aufgabe",
		"Auge",
		"Ausbildung",
		"Auskunft",
		"Ausl√§nderin",
		"Aussage",
		"Ausstellung",
		"Autobahn",
		"B√§ckerei",
		"Bahn",
		"Banane",
		"Bank",
		"Batterie",
		"Beamte",
		"Beamtin",
		"Bekannte",
		"Beratung",
		"Berufsschule",
		"Bewerbung",
		"Birne",
		"Bitte",
		"Blume",
		"Bluse",
		"Bohne",
		"Br√ºcke",
		"Briefmarke",
		"Brieftasche",
		"Brille",
		"Butter",
		"CD",
		"CD",
		"Creme",
		"Dame",
		"Dauer",
		"Deutsche",
		"Disco",
		"Durchsage",
		"Dusche",
		"Ecke",
		"Ehefrau",
		"Einf√ºhrung",
		"Einladung",
		"Eltern",
		"Entschuldigung",
		"Erfahrung",
		"Erlaubnis",
		"Erm√§√üigung",
		"Erwachsene",
		"F√§hre",
		"F√ºhrung",
		"Fabrik",
		"Fahrkarte",
		"Familie",
		"Farbe",
		"Ferien",
		"Feuerwehr",
		"Firma",
		"Flasche",
		"Flur",
		"Frage",
		"Frau",
		"Freizeit",
		"Freundin",
		"Frist",
		"Gabel",
		"Garage",
		"Geb√ºhr",
		"Geldb√∂rse",
		"Gesamtschule",
		"Geschwister",
		"Gesundheit",
		"Gr√∂√üe",
		"Grippe",
		"Gro√üeltern",
		"Gro√ümutter",
		"Grundschule",
		"Gruppe",
		"Halbpension",
		"Halle",
		"Haltestelle",
		"Hand",
		"Hausaufgabe",
		"Hausfrau",
		"Heimat",
		"Heizung",
		"Hilfe",
		"Hose",
		"Idee",
		"Industrie",
		"Information",
		"Jacke",
		"Jugendherberge",
		"Jugendliche",
		"K√ºche",
		"K√ºndigung",
		"Kamera",
		"Kanne",
		"Karte",
		"Kartoffel",
		"Kasse",
		"Kassette",
		"Katze",
		"Kenntnisse",
		"Kette",
		"Kirche",
		"Klasse",
		"Kleidung",
		"Kneipe",
		"Kollegin",
		"Kontrolle",
		"Kosmetik",
		"Krankenkasse",
		"Krankheit",
		"Kreditkarte",
		"Kreuzung",
		"Kunde",
		"Kundin",
		"L√∂sung",
		"Lampe",
		"Landschaft",
		"Lebensmittel",
		"Lehre",
		"Lehrerin",
		"Leute",
		"Lohn",
		"Luft",
		"Lust",
		"M√∂bel",
		"M√ºlltonne",
		"Maschine",
		"Mehrwertsteuer",
		"Meinung",
		"Menge",
		"Miete",
		"Milch",
		"Minute",
		"Mitte",
		"Mitteilung",
		"Mittelschule",
		"Mode",
		"Musik",
		"Mutter",
		"N√§he",
		"Nachbarin",
		"Nacht",
		"Natur",
		"Note",
		"Notiz",
		"Nudel",
		"Nummer",
		"Oma",
		"Operation",
		"Orange",
		"Ordnung",
		"Panne",
		"Partei",
		"Partnerin",
		"Party",
		"Pause",
		"Pension",
		"Plastik",
		"Polizei",
		"Portion",
		"Post",
		"Postleitzahl",
		"Pr√ºfung",
		"Praxis",
		"Qualit√§t",
		"Quittung",
		"Raucherin",
		"Realschule",
		"Rechnung",
		"Reinigung",
		"Reise",
		"Reparatur",
		"Rezeption",
		"Ros√©",
		"Rose",
		"Sache",
		"Sch√ºlerin",
		"Scheckkarte",
		"Schokolade",
		"Schule",
		"Schwester",
		"See",
		"Sehensw√ºrdigkeit",
		"Seife",
		"Sekret√§rin",
		"Sekunde",
		"Sendung",
		"Sonne",
		"Sorge",
		"Sp√ºlmaschine",
		"Speisekarte",
		"Sprache",
		"Sprachschule",
		"Sprechstunde",
		"Stadt",
		"Steuer",
		"Stra√üe",
		"Stra√üenbahn",
		"Studentin",
		"Stunde",
		"Suppe",
		"T√ºr",
		"T√ºte",
		"Tankstelle",
		"Tasche",
		"Tasse",
		"Tochter",
		"Toilette",
		"Tomate",
		"Treppe",
		"T√ºr",
		"Uhr",
		"Universit√§t",
		"Unterhaltung",
		"Unterkunft",
		"Unterschrift",
		"Untersuchung",
		"Verbindung",
		"Verk√§uferin",
		"Versicherung",
		"Versp√§tung",
		"Volksschule",
		"Vorsicht",
		"Vorwahl",
		"W√§sche",
		"Welt",
		"Werkstatt",
		"Wirtschaft",
		"Woche",
		"Wohnung",
		"Wolke",
		"Wurst",
		"Zahl",
		"Zeit",
		"Zeitschrift",
		"Zeitung",
		"Zigarette",
		"Zitrone",
		0
	};
	const char *cs[] = {
		"Alter",
		"Angebot",
		"Appartement",
		"Auge",
		"Ausland",
		"Auto",
		"B√ºro",
		"Baby",
		"Bad",
		"Bein",
		"Beispiel",
		"Benzin",
		"Bett",
		"Bier",
		"Bild",
		"Blatt",
		"Blut",
		"Br√∂tchen",
		"Brot",
		"Buch",
		"Cafe",
		"Dach",
		"Datum",
		"Ding",
		"Doppelzimmer",
		"Dorf",
		"Ei",
		"Einzelzimmer",
		"Eis",
		"Ende",
		"Erdgeschoss",
		"Ergebnis",
		"Essen",
		"Fahrrad",
		"Fax",
		"Fenster",
		"Fernsehger√§t",
		"Fest",
		"Feuer",
		"Feuerzeug",
		"Fieber",
		"Fleisch",
		"Flugzeug",
		"Formular",
		"Foto",
		"Fr√ºhjahr",
		"Fr√ºhst√ºck",
		"Fundb√ºro",
		"Gas",
		"Geburtsjahr",
		"Gegenteil",
		"Geld",
		"Gem√ºse",
		"Gep√§ck",
		"Gericht",
		"Gesch√§ft",
		"Geschenk",
		"Geschirr",
		"Gesicht",
		"Gespr√§ch",
		"Getr√§nk",
		"Gewicht",
		"Gewitter",
		"Gl√ºck",
		"Glas",
		"Gleis",
		"Guthaben",
		"Gymnasium",
		"H√§hnchen",
		"Haar",
		"Handtuch",
		"Handy",
		"Haus",
		"Hemd",
		"Herz",
		"Hobby",
		"Holz",
		"Internet",
		"Jahr",
		"Junge",
		"Kennzeichen",
		"Kfz",
		"Kind",
		"Kino",
		"Kleid",
		"Konsulat",
		"Konto",
		"Konzert",
		"Laden",
		"Lager",
		"Land",
		"Leben",
		"Lebensmittel",
		"Leid",
		"Licht",
		"Lied",
		"Loch",
		"Lokal",
		"M√§dchen",
		"M√∂bel",
		"Mal",
		"Material",
		"Medikament",
		"Meer",
		"Messer",
		"Metall",
		"Mittel",
		"Moment",
		"Morgen",
		"Museum",
		"Obst",
		"√ñl",
		"P√§ckchen",
		"Paket",
		"Papier",
		"Parf√ºm",
		"Plastik",
		"Praktikum",
		"Problem",
		"Programm",
		"R√ºcken",
		"Radio",
		"Rathaus",
		"Reifen",
		"Reis",
		"Reiseb√ºro",
		"Restaurant",
		"Rezept",
		"Rind",
		"Ros√©",
		"Salz",
		"Schiff",
		"Schild",
		"Schloss",
		"Schwein",
		"Schwimmbad",
		"Service",
		"Sofa",
		"Sonderangebot",
		"St√ºck",
		"Standesamt",
		"Steuer",
		"Streichholz",
		"Studium",
		"Tag",
		"Taxi",
		"Teil",
		"Telefon",
		"Telefonbuch",
		"Theater",
		"Thema",
		"Ticket",
		"Tier",
		"Trinkgeld",
		"Video",
		"Wasser",
		"Werkzeug",
		"Wetter",
		"Wiederh√∂ren",
		"Wiedersehen",
		"Wochenende",
		"Wort",
		"Zentrum",
		"Zeugnis",
		"Zimmer",
		0
	};
	
	switch(kng.genus) {
		case Maskulinum:
			xs = as;
			break;
		case Femininum:
			xs = bs;
			break;
		case Neutrum:
			xs = cs;
			break;
	};

	const char **v = xs;
	while(*v) ++v;
	const long n = v - xs - 1;
	const char **r = xs + (n * (long long)_rand() / (long long)RAND_MAX);

	switch(kng.kasus) {
		case Nominativ:
			switch(kng.numerus) {
				case Singular:
					return r[0];
				case Plural:
					return string(r[0]) + "en";
			}
		case Akkusativ:
			switch(kng.numerus) {
				case Singular:
					return r[0];
				case Plural:
					return string(r[0]) + "en";
			}
		case Genitiv:
			switch(kng.numerus) {
				case Singular:
					switch(kng.genus) {
						case Maskulinum: return string(r[0]) + "s";
						case Femininum: return string(r[0]);
						case Neutrum: return string(r[0]) + "s";
					}
				case Plural:
					switch(kng.genus) {
						case Maskulinum: return string(r[0]) + "en";
						case Femininum: return string(r[0]) + "en";
						case Neutrum: return string(r[0]) + "en";
					}
			}
	}
}





inline string sentence() {
	KNG subjectKNG;
	KNG subjectGenitivKNG;
	KNG objectKNG;
	KNG objectGenitivKNG;
	TNP predicateTNP;
	TNP subjectGenitivTNP;
	TNP objectGenitivTNP;

	subjectKNG.kasus = Nominativ;
	subjectGenitivKNG.kasus = Genitiv;
	objectKNG.kasus = Akkusativ;
	objectGenitivKNG.kasus = Genitiv;
	predicateTNP.numerus = subjectKNG.numerus;
	subjectGenitivTNP.numerus = subjectGenitivKNG.numerus;
	objectGenitivTNP.numerus = objectGenitivKNG.numerus;
	
	bool subjectDirect = (long long)_rand() % 2;
	bool subjectGenitivDirect = (long long)_rand() % 2;
	bool objectDirect = (long long)_rand() % 2;
	bool objectGenitivDirect = (long long)_rand() % 2;

	//eg (KNG Konguenz)
	//"der dicke Hund eines angestellten Fahrers geht verkr√ºppelt √ºber die aufgeheizte Stra√üe einer l√§ssigen Partei"
	
	Verb v = verb(predicateTNP);

	stringstream ss;
	ss << article(subjectDirect,subjectKNG,predicateTNP) + " " + adjective(subjectDirect,subjectKNG) + " " + noun(subjectDirect,subjectKNG);
	ss << " ";
	ss << article(subjectGenitivDirect,subjectGenitivKNG,subjectGenitivTNP) + " " + adjective(subjectGenitivDirect,subjectGenitivKNG) + " " + noun(subjectGenitivDirect,subjectGenitivKNG);
	ss << " ";
	ss << v.hilfsverb;
	ss << " ";
	ss << article(objectDirect,objectKNG,predicateTNP) + " " + adjective(objectDirect,objectKNG) + " " + noun(objectDirect,objectKNG);
	ss << " ";
	ss << article(objectGenitivDirect,objectGenitivKNG,objectGenitivTNP) + " " + adjective(objectGenitivDirect,objectGenitivKNG) + " " + noun(objectGenitivDirect,objectGenitivKNG);
	ss << " ";
	ss << v.verb;

	return ss.str();
}



int main(int argc,char **argv) {
	_srand();

	string s = sentence();
	
	cout << (char)(s[0] - 'a' + 'A') << s.substr(1) << "." << endl;

	return 0;
}




#//Dynamic Signature : Sie Weihnachtskonten Ihres ultimativen Gerichts, die zappeligen Credits von taktvollem M√ºll werden gestartet.
#//Dynamic Signature : Ein olympiatauglicher Funktion√§r mehrerer Sachrunden l√∂scht die sachverst√§ndigen Wetter eines theoretischen Gutachtens.
#//Dynamic Signature : Das jordanische Fernsehen mit chronologischen Antworten verzerrte die luftige Ladung mehrerer spitzer Bildschirme.
#//Dynamic Signature : Das mentale Angebot eines ehrgeizigen Gl√ºckwunschs rinnst deinen fadenscheinigen Briefkasten der bairischen Blicken .
#//PGP : â≥ 
 !Lf¸@chWßÂ_5CÕs	íc‘ô 
	_5CÕs	íyW é·⁄FÖ‚IÛWéfÖø6´BÏÄÒk_+ñü6UË16ÿ,ô8ﬂ~Éb≠Àç&Ù+ˆ≥∑rXÉ'õ÷÷~;ΩHŒù#∞Á/£% _S !˙∏ú36BQÏç‹ùÄ FgúYë!2ñUÎ^…zæ'~YÆ≈Ë¥3gƒ›Üu4ºr!◊`k—,´‹Ô—3=Ω™rJCº:ß6yL
ÿA˜RÍy`T=∏RóoB◊1v!J=ƒü&\ÍüäNè|éï|ç…_{Ö$‚.T≥Y1ôé+mπüi ,RÀï≈Z N∆Ó7ê]§ùz§¸9"iÅ;hã&]œ»ã\^0C@>è„ õ<ˇ·¶≥¡{;≤L˛9˝UÕªõ©Œ“∂÷∂¶PﬁÏ®‚^∑Ÿh°iwEùÍCAÏb‚“#3•ƒÁ26-ÎoI@Õñ†ô“â¶≈DIÔG£7+ÎM5V]œp¡ú‰"dr-∞tÈK˝÷Ω∞ﬁ´N¡ï‰ ND»Wë]›Pê¿ÈÏ—’‡ˆ