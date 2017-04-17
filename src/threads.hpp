#ifndef __THREADS_HPP__
#define __THREADS_HPP__

#include "afxmt.h"

namespace Dot {

	namespace Threading { 

///////////////////////////////////////////////////////////////////////////
//	class SingleThreaded
///////////////////////////////////////////////////////////////////////////

		//	Defines the locking mechanisim for single threaded model
		//	which is actually empty
		template<typename T>
		class SingleThreaded {
		public : 
			typedef T VolatileType;

		protected : 
			inline explicit SingleThreaded() {}
			inline ~SingleThreaded() {}

		protected : 
			//	Perform thread locks
			class LockThread {
			public : 
				inline explicit LockThread() { SingleThreaded::Lock(); }
	            inline ~LockThread() { SingleThreaded::Unlock(); }

			private : 
				inline explicit LockThread(LockThread const&) {}
				inline LockThread& operator=(LockThread const&) { return *this; }
			};	//	end of class LockThread

		private : 
			//	thread synchronization helps
			friend LockThread;

			inline static void Lock() {}
			inline static void Unlock() {}

		private : 
			inline explicit SingleThreaded(SingleThreaded const&) {}
			inline SingleThreaded& operator=(SingleThreaded const&) { return *this; }
		};	//	end of class SingleThreaded

///////////////////////////////////////////////////////////////////////////
//	class MultiThreaded
///////////////////////////////////////////////////////////////////////////

		//	Defines the locking mechanisim for multi threaded model
		//	which is actually empty
		template<typename T>
		class MultiThreaded {
		public : 
			typedef T VolatileType;

		protected : 
			inline explicit MultiThreaded() {}
			inline ~MultiThreaded() {}

		protected : 
			//	Perform thread locks
			class LockThread {
			public : 
				inline explicit LockThread() { MultiThreaded::Lock(); }
	            inline ~LockThread() { MultiThreaded::Unlock(); }

			private : 
				inline explicit LockThread(LockThread const&) {}
				inline LockThread& operator=(LockThread const&) { return *this; }
			};	//	end of class LockThread

		private : 
			//	thread synchronization helps
			friend LockThread;

			static CCriticalSection criticalsection_;

			inline static void Lock()  {criticalsection_.Lock();}
			inline static void Unlock(){criticalsection_.Unlock();}

		private : 
			inline explicit MultiThreaded(MultiThreaded const&) {}
			inline MultiThreaded& operator=(MultiThreaded const&) { return *this; }
		};	//	end of class MultiThreaded

		template<typename T>
		CCriticalSection MultiThreaded<T>::criticalsection_;

	};	//	end of namespace Threading

};	//	end of namespace Dot

#endif