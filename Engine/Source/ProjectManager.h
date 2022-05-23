#pragma once

// User-defined Headers
#include "Core\Init\init_glut.h"
#include "../Source/Render/Scene.h"
#include "Core\PluginInterface.h"
namespace  HoloGraphicEngine
{
	/**
	 * Primary Engine Interface to be used to setup scenes
	 */
	class ProjectManager
	{
	public:

		/**
		 * ProjectManager Default Constructor
		 */
		ProjectManager();

		/**
		* ProjectManager Default Destructor
		*/
		~ProjectManager();

		/**
		 * Initializes OpenGL context and all the managers
		 */
		bool Init(int position_x, int position_y,  int width , int height );
	 

		/**
		 * Engine's main run method
		 * Calls InitGLUT::Run()
		 */
		void Run();

		/**
		 * Return engine's scene manager
		 * @return scene manager
		 */
		Scene*  GetScene()  const;
 
		 

		/**
		* Return engine's camera manager
		* @return camera manager
		*/
		Camera* GetCamera() const;

 
	private:

		/* Engine's main Scene manager object */
		Scene*  Scene_;
 
		/* Engine's main Camera Manager - Same one set in Scene manager */
		Camera* Camera_;

		std::map<std::string, PluginInterface*>  PluginInterface_;
	};
}