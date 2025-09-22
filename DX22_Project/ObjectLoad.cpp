#include "ObjectLoad.h"
#include "RendererComponent.h"

void CObjectLoad::LoadAll()
{
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Result.jpg"), "ResultBG");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Fade.png"), "Fade");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Title.jpg"), "TitleBG");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Alphabet.png"), "Alphabet");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("SelectBackGround.jpeg"), "SelectBG");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Stageselect_Left01.png"), "ArrowLeft");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Stageselect_Right01.png"), "ArrowRight");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Jobs.png"), "Player");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Slime.png"), "Slime");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("HPBar.jpg"), "HPBar");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Number.png"), "Number");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Ghost.png"), "Ghost");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Dragon.png"), "Dragon");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/SwordNormalSkill.png"), "SwordNormalAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/SwordQSkill.png"), "SwordQSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/SwordESkill.png"), "SwordESkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/SwordRSkill.png"), "SwordRSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/WizardNormalSkill.png"), "WizardNormalAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/WizardQSkill.png"), "WizardQSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/WizardESkill.png"), "WizardESkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/WizardESkill2.png"), "WizardESkill2");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/WizardRSkill.png"), "WizardRSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterNormalSkill.png"), "FighterNormalAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkill.png"), "FighterQSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkillCharge1.png"), "FighterQSkillCharge1");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkillCharge2.png"), "FighterQSkillCharge2");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkillCharge3.png"), "FighterQSkillCharge3");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkillCharge4.png"), "FighterQSkillCharge4");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterQSkillCharge5.png"), "FighterQSkillCharge5");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterESkill.png"), "FighterESkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/FighterRSkill.png"), "FighterRSkill");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/PlayerAttackHit.png"), "PlayerAttackHit");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/SlimeAttack.png"), "SlimeAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/GhostAttack.png"), "GhostAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/DragonNormalAttack.png"), "DragonNormalAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Effect/DragonBreathAttack.png"), "DragonBreathAttack");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Circle.png"), "Circle");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Frame.png"), "Frame");
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Mouse.png"), "MouseUI");
    CRendererComponent::Load(RendererKind::Model, MODEL_PATH("Ground.obj"), "Field", 1.0f, Model::Flip::XFlip);
    CRendererComponent::Load(RendererKind::Model, MODEL_PATH("SkyBox.obj"), "SkyBox", 100000.0f);
}

void CObjectLoad::UnLoadAll()
{
    CRendererComponent::UnLoad();
}
