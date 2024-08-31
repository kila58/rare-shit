#define  asrt( _exp ) ((void)0)

float fbits_to_float(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = fbits_to_float((unsigned long)0x7FC00000);
			}
		}
	}

	float *operator[](int i)				{ asrt((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float *operator[](int i) const	{ asrt((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float *Base()							{ return &m_flMatVal[0][0]; }
	const float *Base() const				{ return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

class matrix
{
public:

	matrix();
	matrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
		);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	matrix(const vector& forward, const vector& left, const vector& up);

	// Construct from a 3x4 matrix
	matrix(const matrix3x4_t& matrix3x4);

	// Set the values in the matrix.
	void		Init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
		);


	// Initialize from a 3x4
	void		Init(const matrix3x4_t& matrix3x4);

	// array access
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float *Base()
	{
		return &m[0][0];
	}

	inline const float *Base() const
	{
		return &m[0][0];
	}

	inline const matrix& operator+=(const matrix &other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] += other.m[i][j];
			}
		}

		return *this;
	}

	inline matrix operator+(const matrix &other) const
	{
		matrix ret;
		for (int i = 0; i < 16; i++)
		{
			((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
		}
		return ret;
	}

public:
	// The matrix.
	float		m[4][4];
};

class ivengineclient
{
public:
	// Find the model's surfaces that intersect the given sphere.
	// Returns the number of surfaces filled in.
	virtual void padding1() = 0;

	// Get the lighting intensivty for a specified point
	// If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
	virtual void padding2() = 0;

	// Traces the line and reports the material impacted as well as the lighting information for the impact point
	virtual void padding3() = 0;

	// Given an input text buffer data pointer, parses a single token into the variable token and returns the new
	//  reading position
	virtual const char			*ParseFile(const char *data, char *token, int maxlen) = 0;
	virtual bool				CopyFile(const char *source, const char *destination) = 0;

	// Gets the dimensions of the game window
	virtual void				get_scrnsize(int& iwidth, int& iheight) = 0;

	// Forwards szCmdString to the server, sent reliably if bReliable is set
	virtual void				ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
	//       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void				ClientCmd(const char *szCmdString) = 0;

	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual void padding4() = 0;

	// Retrieve the player entity number for a specified userID
	virtual int					iget_player_by_id(int userID) = 0;

	// Retrieves text message system information for the specified message by name
	virtual void padding5() = 0;

	// Returns true if the console is visible
	virtual bool				Con_IsVisible(void) = 0;

	// Get the entity index of the local player
	virtual int					get_me(void) = 0;

	// Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
	virtual void padding6() = 0;

	// Get the exact server timesstamp ( server time ) from the last message received from the server
	virtual float				GetLastTimeStamp(void) = 0;

	// Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
	//  captioning data )
	virtual void padding7() = 0;
	// Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
	virtual void padding8() = 0;
	// Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
	virtual void padding0() = 0;

	// Copy current view orientation into va
	virtual void				get_viewangles(qangle& qva) = 0;
	// Set current view orientation from va
	virtual void				set_viewangles(qangle& qva) = 0;

	// Retrieve the current game's maxclients setting
	virtual int					GetMaxClients(void) = 0; // 20

	// Given the string pBinding which may be bound to a key, 
	//  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
	virtual	const char			*Key_LookupBinding(const char *pBinding) = 0;

	// Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
	virtual void padding10() = 0;
	virtual void padding11() = 0;

	// key trapping (for binding keys)
	virtual void				StartKeyTrapMode(void) = 0;
	virtual void padding12() = 0;

	// Returns true if the player is fully connected and active in game (i.e, not still loading)
	virtual bool				in_game(void) = 0;
	// Returns true if the player is connected, but not necessarily active in game (could still be loading)
	virtual bool				IsConnected(void) = 0;
	// Returns true if the loading plaque should be drawn
	virtual bool				IsDrawingLoadingImage(void) = 0;
	virtual void				HideLoadingPlaque(void) = 0;

	// Prints the formatted string to the notification area of the screen ( down the right hand edge
	//  numbered lines starting at position 0
	virtual void				Con_NPrintf(int pos, const char *fmt, ...) = 0; // 30
	// Similar to Con_NPrintf, but allows specifying custom text color and duration information
	virtual void				Con_NXPrintf(const struct con_nprint_s *info, const char *fmt, ...) = 0;

	// Is the specified world-space bounding box inside the view frustum?
	virtual void padding13() = 0;

	// Is the specified world-space boudning box in the same PVS cluster as the view origin?
	virtual void padding14() = 0;

	// Returns true if the specified box is outside of the view frustum and should be culled
	virtual void padding15() = 0;

	// Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
	virtual void				Sound_ExtraUpdate(void) = 0;

	// Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
	virtual const char			*GetGameDirectory(void) = 0;

	// Get access to the world to screen transformation matrix
	virtual const matrix& 		get_worldtoscreen_matrix() = 0;

	// Get the matrix to move a point from world space into view space
	// (translate and rotate so the camera is at the origin looking down X).
	virtual const matrix& 		get_view_matrix() = 0;
};