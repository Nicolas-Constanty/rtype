#pragma once

#ifndef IDLLLOADER_HPP_
# define IDLLLOADER_HPP_

/**
 * \brief Loader interface for dll files.
 * T Should be the return type handling the DLL loaded.
 */
template <class T>
class ILibraryLoader
{
public:
	virtual ~ILibraryLoader() {}

public:
	virtual T Load(std::string const& path) = 0;
	virtual int Unload() = 0;
};

#endif