#ifndef Fonts_hpp
#define Fonts_hpp


sf::Font basicFont;
sf::Font dialogBoxFont;


void loadFonts() {
	basicFont = sf::Font();
	basicFont.loadFromFile("assets/fonts/arial.ttf");

	dialogBoxFont = sf::Font();
	dialogBoxFont.loadFromFile("assets/fonts/CascadiaCode.ttf");

}


std::wstring ConvertUtf8ToWide(const std::string& utf8Str) {
    // TO-DO
    short wideCharCount = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), utf8Str.size(), nullptr, 0);
    if (wideCharCount == 0) {
        throw std::runtime_error("Error in MultiByteToWideChar");
    }

    std::wstring wideStr(wideCharCount, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), utf8Str.size(), &wideStr[0], wideCharCount);
    return wideStr;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Zmieniamy start_pos o długość "to" aby uniknąć zapętlenia
    }
}


std::vector < std::wstring > wrapText(std::wstring text, const sf::Font& font, short characterSize, short maxWidth) {

    std::vector < std::wstring > wrappedText;

    std::wistringstream wordsStream(text);
    std::wstring word;
    std::wstring currentLine;

    while (std::getline(wordsStream, word, L' ')) {

        // przetwarzanie enterów
        std::size_t newLinePos;
        while ((newLinePos = word.find(L'\n')) != std::wstring::npos) {

            std::wstring beforeNewLine = word.substr(0, newLinePos);
            std::wstring testLine = (currentLine.empty())? beforeNewLine : currentLine + L" " + beforeNewLine;
            sf::Text testText(testLine, font, characterSize);

            if (!testLine.empty() && testText.getLocalBounds().width >= maxWidth) {
                wrappedText.push_back(currentLine);
                currentLine = beforeNewLine;
            }
            else {
                currentLine = testLine;
            }

            wrappedText.push_back(currentLine);
            currentLine.clear();
            word = word.substr(newLinePos + 1);
        }

        // przetwarzanie tekstu
        std::wstring testLine = (currentLine.empty())? word : currentLine + L" " + word;
        sf::Text testText(testLine, font, characterSize);

        if ( maxWidth>0.0f && testText.getLocalBounds().width >= maxWidth) {
            wrappedText.push_back(currentLine);
            currentLine = word;
        }
        else {
            currentLine = testLine;
        }
    }

    if (!currentLine.empty()) {
        wrappedText.push_back(currentLine);
    }

    if (wrappedText.size() == 0)
        wrappedText.push_back(L"");

    return wrappedText;
}

std::string getShortName(std::string fullname) {

	std::string shortname = "";
	for (int i = fullname.size() - 1; i >= 0 && fullname[i] != '/' && fullname[i] != '\\'; i--) {
		shortname = fullname[i] + shortname;
	}

	return shortname;
}

std::wstring getShortName(std::wstring fullname) {

	std::wstring shortname = L"";
	for (int i = fullname.size() - 1; i >= 0 && fullname[i] != L'/' && fullname[i] != '\\'; i--) {
		shortname = fullname[i] + shortname;
	}

	return shortname;
}
#endif