#pragma once
namespace HoloGraphicEngine {

	 
	class PluginInterface
	{
	public:

		// Pure Virtual Destructor
		virtual ~PluginInterface() = 0;

		// Display Functions
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnDestroy() = 0;
		 
	};

	// Implementation of Pure Virtual Destructor
	inline PluginInterface::~PluginInterface() {}
}