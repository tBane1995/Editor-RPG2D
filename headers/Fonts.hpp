#ifndef Fonts_hpp
#define Fonts_hpp


sf::Font basicFont;
sf::Font dialogueFont;


void loadFonts() {
	basicFont = sf::Font();
	//basicFont.loadFromFile("assets\\fonts\\arial.ttf");
	basicFont.loadFromFile("assets\\fonts\\Tiny5-Regular.ttf");

	dialogueFont = sf::Font();
	dialogueFont.loadFromFile("assets\\fonts\\Pixelify_Sans\\PixelifySans-VariableFont_wght.ttf");

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

std::string ConvertWideToUtf8(std::wstring wide) {
    return std::string(wide.begin(), wide.end());
}

std::vector < std::wstring > wrapText(const std::wstring& text, const sf::Font& font, short characterSize, short maxWidth)
{
    std::vector < std::wstring > result;
    std::wistringstream lineStream(text);
    std::wstring paragraph;

    // Przetwarzamy tekst linia po linii (rozdzielone znakiem '\n')
    while (std::getline(lineStream, paragraph, L'\n'))
    {
        std::wstring currentLine;

        // Sprawdzamy, czy akapit rozpoczyna się spacjami (np. indent)
        if (!paragraph.empty() && paragraph[0] == L' ')
        {
            // Znajdź liczbę początkowych spacji.
            size_t firstNonSpace = paragraph.find_first_not_of(L' ');
            if (firstNonSpace == std::wstring::npos)
            {
                // Akapit zawiera tylko spacje – dodajemy go do wyniku i przechodzimy do kolejnej linii
                result.push_back(paragraph);
                continue;
            }
            // Zachowujemy indent w currentLine i usuwamy je z akapitu.
            currentLine = paragraph.substr(0, firstNonSpace);
            paragraph = paragraph.substr(firstNonSpace);
        }

        // Jeśli po usunięciu indentu akapit jest pusty, dodajemy go (np. linia składająca się tylko ze spacji)
        if (paragraph.empty())
        {
            result.push_back(currentLine);
            continue;
        }

        // Używamy stringstream do dzielenia akapitu na "słowa" – operator >> nie zachowa spacji,
        // ale indent już umieszczony w currentLine zostaje.
        std::wistringstream wordStream(paragraph);
        std::wstring word;

        while (wordStream >> word)
        {
            std::wstring testLine;
            // Jeśli currentLine jest puste, to testLine to po prostu słowo
            // w przeciwnym razie, wstawiamy spację między bieżącą linią a kolejnym słowem.
            if (currentLine.empty())
                testLine = word;
            else
            {
                // Jeśli currentLine kończy się spacją (np. indent), nie trzeba dodawać dodatkowej spacji
                if (currentLine.back() == L' ')
                    testLine = currentLine + word;
                else
                    testLine = currentLine + L" " + word;

            }

            if (maxWidth > 0)
            {
                // Tworzymy obiekt sf::Text, aby zmierzyć szerokość wygenerowanej linii.
                sf::Text sfText(testLine, font, characterSize);
                float width = sfText.getLocalBounds().width;

                if (width > maxWidth)
                {
                    // Jeśli bieżąca linia (bez nowego słowa) nie jest pusta, dodajemy ją do wyniku i rozpoczynamy nową linię
                    if (!currentLine.empty())
                    {
                        result.push_back(currentLine);
                        currentLine = word; // rozpoczęcie nowej linii od nowego słowa
                    }
                    else
                    {
                        // Jeśli pojedyncze słowo przekracza maxWidth to i tak je dodajemy osobno
                        result.push_back(word);
                        currentLine.clear();
                    }
                }
                else
                {
                    currentLine = testLine;
                }
            }
            else
            {
                // Brak ograniczenia szerokości – po prostu łączymy słowa
                currentLine = testLine;
            }
        }

        // Po przetworzeniu akapitu dodajemy ostatnią linie (nawet jeśli jest pusta albo zawiera tylko indent)
        result.push_back(currentLine);
        // currentLine jest czyszczone na potrzeby kolejnego akapitu
        currentLine.clear();
    }

    // Jeśli oryginalny tekst kończył się znakiem nowej linii, dodajemy pustą linię.
    if (!text.empty() && text.back() == L'\n')
    {
        result.push_back(L"");
    }

    // Jeśli wynik jest pusty, zwracamy jedną pustą linię.
    if (result.empty())
    {
        result.push_back(L"");
    }

    return result;
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