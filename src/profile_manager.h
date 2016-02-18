/**
Lightweight profiler library for c++
Copyright(C) 2016  Sergey Yagovtsev

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef ___PROFILER____MANAGER____H______
#define ___PROFILER____MANAGER____H______

#include "profiler/profiler.h"

#include "spin_lock.h"

#include <stack>
#include <map>

class ProfileManager
{
	ProfileManager();
	ProfileManager(const ProfileManager& p) = delete;
	ProfileManager& operator=(const ProfileManager&) = delete;
    static ProfileManager m_profileManager;

	bool m_isEnabled = false;

	typedef std::stack<profiler::Block*> stack_of_blocks_t;
	typedef std::map<size_t, stack_of_blocks_t> map_of_threads_stacks;

	map_of_threads_stacks m_openedBracketsMap;

	profiler::spin_lock m_spin;
	typedef profiler::guard_lock<profiler::spin_lock> guard_lock_t;
public:
    static ProfileManager& instance();

	void registerMark(profiler::Mark* _mark);
	void beginBlock(profiler::Block* _block);
	void endBlock();
	void setEnabled(bool isEnable);
};

#endif
