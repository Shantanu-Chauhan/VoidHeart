function CreateFireball(xVel, zVel)
	attackPosition = gameObject:GetTransform().position

	local gameObjectPath = "Resources/Json data/PlayerBullet.json"
	go = CreateGameObject(gameObjectPath)
	body = go:GetBody()
	body.position = attackPosition
		
	local xVelocity = GetAxis(CONTROLLER["RX"])
	local zVelocity = GetAxis(CONTROLLER["RY"])
	local totalVelocity = math.sqrt(xVelocity*xVelocity + zVelocity*zVelocity)
	xVelocity = xVelocity / totalVelocity
	zVelocity = zVelocity / totalVelocity
		
	local attackSpeed = 5.0
	body.velocity = attackSpeed * vec3.new(xVelocity, 0.0, zVelocity)

	transform = go:GetTransform()
	transform.position = body.position

	-- Change Color
	material = go:GetMaterial()
	material.diffuse = vec3.new(4.0, 0.0, 0.0)
end

function PlayerAttack ()
	for i=1,3 do
		CreateFireball(i, i)
	end
	PlaySFX("Resources/Audio/SFX/PlayerAttack.wav")
end

function CheckValidAttack()
	attack = gameObject:GetAttack()
	if attack.shouldAttack and (attack.currentAttackTime > attack.baseAttackTime) then
		PlayerAttack()
		attack.currentAttackTime = 0.0
		attack.shouldAttack = false;
	end
end

CheckValidAttack()