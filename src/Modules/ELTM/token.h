// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 14/05/2021

#ifndef __ELTM_TOKEN__
#define __ELTM_TOKEN__

#include <AEpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>

namespace AE
{
	enum eltm_token
	{
		kw_set,
		kw_import,

		kw_begin,
		kw_end,
		
		kw_module,			// "kw_" are keywords

		basic_comment,
		begin_long_comment,
		end_long_comment,

		kw_get,
		assign,
		
		error
	};

	class Token
	{
		public:
			Token(std::variant<eltm_token, std::string> value, size_t line, size_t index);

			static inline std::map<std::string, eltm_token> keyword_token
			{
				{"set", kw_set},
				{"=", assign},
				{"get", kw_get},

				{"import", kw_import},

				{"begin", kw_begin},
				{"end", kw_end},

				{"module", kw_module},

				{"//", basic_comment},
				{"/*", begin_long_comment},
				{"*/", end_long_comment},
			};

			bool isString();
			bool isKeyword();
			
			std::string getString(std::string file, std::string caller, size_t line)
			{
				if(isString())
					return std::get<std::string>(_value);
				ELTMerrors error = context_error("token : this token is not a string", file, caller, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}
			eltm_token getReservedToken(std::string file, std::string caller, size_t line)
			{
				if(isKeyword())
					return std::get<eltm_token>(_value);
				ELTMerrors func_error = context_error("token : this token is not a reserved token", file, caller, line);
				std::cout << red << func_error.what() << def << std::endl;
				return error;
			}
			size_t getLine();
			size_t getIndex();
			
		private:
			std::variant<eltm_token, std::string> _value;
			size_t _line;
			size_t _index;
	};

	#undef getString
	#define getString() getString(__FILE__, __FUNCTION__, __LINE__)
	#undef getReservedToken
	#define getReservedToken() getReservedToken(__FILE__, __FUNCTION__, __LINE__)
}

#endif // __ELTM_TOKEN__
