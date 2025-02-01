#pragma once

//defines a Symbol Map generated by the compiler

#include <CubasicVenders/json.hpp>

#include <fstream>

namespace Cubasic::Symbol
{
	//defines the kind of symbol
	enum class SymbolType
	{
		Function = 0, //does the symbol point to a function name
		Var, //does the symbol point to a variable

		//does this symbol point to a string literal

		Count
	};

	//defines a symbol
	struct Symbol
	{
		SymbolType type = SymbolType::Count; //what kind of symbol is this
		uint64_t ID = 0; //the ID associated with the symbol
		std::string name = ""; //the real name associated with this symbol

		//generates a JSON array entry
		inline nlohmann::json GenerateJSONArrayEntry() const
		{
			return nlohmann::json{ {"symbolName", name}, {"ID", ID}, {"type", type} };
		}

		//parses a JSON array entry
	};

	//defines a symbol map
	struct SymbolMap
	{
		uint64_t nextSymbolID = 0; //the next ID we can give to a symbol

		std::vector<Symbol> symbols;

		//creates a new symbol
		inline Symbol& CreateNewSymbol(const std::string& strName)
		{
			//generates a ID
			uint64_t ID = nextSymbolID;
			nextSymbolID++;

			Symbol sym; sym.ID = ID; sym.name = strName;
			return symbols.emplace_back(sym);
		}

		//checks if a symbol exists and gets it if it does.
		//if it does not, create a new one
		inline Symbol* GetSymbol(const std::string& name)
		{
			//checks if it exists
			Symbol* sym = nullptr;
			for (size_t i = 0; i < symbols.size(); ++i)
			{
				if(!strcmp(symbols[i].name.c_str(), name.c_str()))
					return &(symbols[i]);
			}

			//if not, create it
			return &CreateNewSymbol(name);
		}

		//checks if a symbol exists and gets it.
		inline Symbol* GetSymbol(const uint64_t& ID)
		{
			//checks if it exists
			Symbol* sym = nullptr;
			for (size_t i = 0; i < symbols.size(); ++i)
			{
				if (symbols[i].ID == ID);
					return &(symbols[i]);
			}

			return sym;
		}

		//writes the symbol map to a file
		inline void WriteToDisc(const std::filesystem::path& filepath, bool isPretty = false)
		{
			std::filesystem::path FP = filepath;

			//checks if it has the extension

			//checks that the directories exist

			//compress symbols and dump
			nlohmann::json ppcMapSymbols = nlohmann::json::array();
			for (size_t i = 0; i < symbols.size(); ++i)
				ppcMapSymbols.emplace_back(symbols[i].GenerateJSONArrayEntry());
			std::ofstream file(FP);
			file << ppcMapSymbols.dump((isPretty == true ? 4 : -1));
		}

		//loads a symbol map from a file
	};
}