#include "main.h"

class GameMovement
{
public:
	GameMovement()
	{
		init = false;
		onground = false;
	}

	inline void ApplyGravity()
	{
		velocity.z -= 1 * sv_gravity->fvalue * 0.5 * engine->globals->interval_per_tick;
	}

	CBaseEntity* player;
	CUserCmd* cmd;
	Vector origin;
	Vector velocity;
	bool init;
	bool onground;
	ConVar* sv_accelerate;
	ConVar* sv_airaccelerate;
	ConVar* sv_friction;
	ConVar* sv_stopspeed;
	ConVar* sv_gravity;

	// funcs
	void CheckParameters() {
		float fmove = cmd->move.x;
		float smove = cmd->move.y;

		float spd = fmove * fmove + smove * smove;
		spd = sqrt2(spd);
		
		if (spd != 0 && spd > 260)
		{
			float ratio = 260/spd;
			
			cmd->move.x = fmove * ratio;
			cmd->move.y = smove * ratio;
		}
	}

	void CategorizePosition() {
		if (velocity.z > 140)
		{
			onground = false;
			return;
		}

		Vector point = origin;
		point.z -= 2;

		Ray_t ray;

		ray.init( origin, point );

		CTraceFilter filter;
		CGameTrace tr;

		filter.pSkip = player;

		engine->TraceRay(ray, filter, tr );

		if (tr.m_pEnt)
			onground = true;
		else
			onground = false;
	}

	void StayInWorld(Vector end) {
		Ray_t ray;

		ray.init( origin, end );

		CTraceFilter filter;
		CGameTrace tr;

		filter.pSkip = player;

		engine->TraceRay(ray, filter, tr );

		if (tr.fraction == 1)
			origin = end;
		else
			origin = tr.endPos;
	}

	void CheckJumpButton() {
		if (!onground)
			return;
		
		onground = false;
		
		velocity.z = velocity.z + (sqrt2(2 * sv_gravity->fvalue * 27) + 20);
		
		ApplyGravity();
	}

	void Friction() {
		float speed = velocity.Length();

		if (speed < 0.1)
			return;

		float drop = 0;

		if (onground)
		{
			float control = speed < sv_stopspeed->fvalue ? sv_stopspeed->fvalue : speed;

			drop = control * sv_friction->fvalue * engine->globals->interval_per_tick;
		}

		float newspeed = max(speed - drop,0);

		if (newspeed != speed)
		{
			newspeed /= speed;
			velocity *= newspeed;
		}
	}

	void Accelerate(Vector wishdir,float wishspeed) {
		float curspeed = velocity.Dot(wishdir);

		float addspeed = wishspeed - curspeed;

		if (addspeed <= 0)
			return;

		float accel = sv_accelerate->fvalue * engine->globals->interval_per_tick * wishspeed;
		accel = min(accel,addspeed);

		velocity += wishdir * accel;
	}

	void AirAccelerate(Vector wishdir,float wishspeed) {
		float curspeed = velocity.Dot(wishdir);

		float addspeed = wishspeed - curspeed;

		if (addspeed <= 0)
			return;

		float accel = sv_airaccelerate->fvalue * engine->globals->interval_per_tick * wishspeed * 0.25;
		accel = min(accel,addspeed);

		velocity += wishdir * accel;
	}

	void WalkMove() {
		Vector angles = cmd->viewangles;

		Vector forward = angles.Forward();
		Vector right = angles.Right();

		forward.z = 0;
		right.z = 0;

		float fmove = cmd->move.x;
		float smove = cmd->move.y;

		Vector wishvel = forward * fmove + right * smove;
		wishvel.z = 0;

		Vector wishdir = wishvel;
		float wishspeed = wishdir.Length();

		if (wishspeed != 0)
			wishdir /= wishspeed;

		wishspeed = min(wishspeed,96); // weapon speed

		Accelerate(wishdir,wishspeed);
		velocity.z = 0;

		if (velocity.Length() < 1)
		{
			velocity = Vector(0,0,0);
			return;
		}

		Vector end = origin + velocity * engine->globals->interval_per_tick;

		StayInWorld(end);
	}

	void AirMove() {
		Vector angles = cmd->viewangles;

		Vector forward = angles.Forward();
		Vector right = angles.Right();

		forward.z = 0;
		right.z = 0;

		float fmove = cmd->move.x;
		float smove = cmd->move.y;

		Vector wishvel = forward * fmove + right * smove;
		wishvel.z = 0;

		Vector wishdir = wishvel;
		float wishspeed = wishdir.Length();

		if (wishspeed != 0)
			wishdir /= wishspeed;

		wishspeed = min(wishspeed,96);

		AirAccelerate(wishdir,min(wishspeed,30));

		Vector end = origin + velocity * engine->globals->interval_per_tick;

		StayInWorld(end);
	}

	void ProcessMovement(CBaseEntity* vplayer,CUserCmd* vcmd) {
		if (!init)
		{
			sv_accelerate = engine->FindVar("sv_accelerate");
			sv_airaccelerate = engine->FindVar("sv_airaccelerate");
			sv_friction = engine->FindVar("sv_friction");
			sv_stopspeed = engine->FindVar("sv_stopspeed");
			sv_gravity = engine->FindVar("sv_gravity");

			init = true;
		}

		player = vplayer;
		cmd = vcmd;

		CheckParameters();

		ApplyGravity();

		if (cmd->buttons & 2)
			CheckJumpButton();

		Friction();

		if (onground)
			WalkMove();
		else
			AirMove();

		CategorizePosition();

		ApplyGravity();

		if (onground)
			velocity.z = 0;
	}
}; extern GameMovement *gameMovement;