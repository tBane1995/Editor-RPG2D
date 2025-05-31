#ifndef Translate_hpp
#define Translate_hpp

enum class Language { English, Polish };

std::vector < std::wstring > English;
std::vector < std::wstring > Polish;

void loadTheLanguages() {

	English.push_back(L"Knife");
	Polish.push_back(L"Nóż");

}

std::wstring getTranslated(int index, Language language) {

	if (index >= English.size()) {
		return L"index range out";
	}

	if (language == Language::English) {
		return English[index];
	}
	
	if (language == Language::Polish) {
		return Polish[index];
	}
		

}

#endif