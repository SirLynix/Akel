// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 17/05/2021

#ifndef __ELTM_CONTEXT__
#define __ELTM_CONTEXT__

#include <AEpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>

namespace AE
{
	class ELTMcontext
	{
		public:
			ELTMcontext();
			bool newContext(const char* file);
			std::string getText(std::string ID, size_t line, std::string file, std::string function)
			{
				if(_isError)
				{
					ELTMerrors error = context_error("context not created due to ELTM errors", file, function, line);
					std::cout << red << error.what() << def << std::endl;
					return "error";
				}

				if(_texts.count(ID))
					return _texts[ID];
				ELTMerrors error = context_error("undefined ID", file, function, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}
			bool setID(int line);

		private:
			bool _isError = false;
			std::map<std::string, std::string> _texts;
			std::map<std::string, std::map<std::string, std::string>> _modules;
			StreamStack _stream;
			const char* _file;
			std::map<std::string, ELTMcontext> _imports;
	};

	#undef getText
	#define getText(ID) getText(ID, __LINE__, __FILE__, __FUNCTION__)
}

#endif // __ELTM_CONTEXT__
