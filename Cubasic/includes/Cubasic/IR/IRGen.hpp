#pragma once

//defines generators for the various subpasses as we turn the tokens into IR

namespace Cubasic::IR
{
	//first pass, collects all the constants and flats digits into streams of digits if needed
	void IRGeneration_FirstPass();

	//second pass, compresses any if, else checks and for loops into their own scopes

	//third pass, compress loops into instructions

	//third pass, checks system calls and moves stuff around for calling them


}