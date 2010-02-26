#include "plAvTaskMsg.h"

/* plAvTaskMsg */
plAvTaskMsg::plAvTaskMsg() : fTask(NULL) { }

plAvTaskMsg::~plAvTaskMsg() {
    if (fTask != NULL)
        delete fTask;
}

IMPLEMENT_CREATABLE(plAvTaskMsg, kAvTaskMsg, plAvatarMsg)

void plAvTaskMsg::read(hsStream* S, plResManager* mgr) {
    plAvatarMsg::read(S, mgr);

    if (S->readBool())
        setTask(plAvTask::Convert(mgr->ReadCreatable(S)));
    else
        setTask(NULL);
}

void plAvTaskMsg::write(hsStream* S, plResManager* mgr) {
    plAvatarMsg::write(S, mgr);

    if (fTask != NULL) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fTask);
    } else {
        S->writeBool(false);
    }
}

void plAvTaskMsg::IPrcWrite(pfPrcHelper* prc) {
    plAvatarMsg::IPrcWrite(prc);

    if (fTask != NULL) {
        prc->writeSimpleTag("Task");
        fTask->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Task");
        prc->writeParam("NULL", true);
        prc->endTag();
    }
}

void plAvTaskMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Task") {
        if (tag->getParam("NULL", "false").toBool())
            setTask(NULL);
        else if (tag->hasChildren())
            setTask(plAvTask::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAvatarMsg::IPrcParse(tag, mgr);
    }
}

plAvTask* plAvTaskMsg::getTask() const { return fTask; }

void plAvTaskMsg::setTask(plAvTask* task) {
    if (fTask != NULL)
        delete fTask;
    fTask = task;
}


/* plAvPushBrainMsg */
plAvPushBrainMsg::plAvPushBrainMsg() : fBrain(NULL) { }

plAvPushBrainMsg::~plAvPushBrainMsg() {
    if (fBrain != NULL)
        delete fBrain;
}

IMPLEMENT_CREATABLE(plAvPushBrainMsg, kAvPushBrainMsg, plAvTaskMsg)

void plAvPushBrainMsg::read(hsStream* S, plResManager* mgr) {
    plAvTaskMsg::read(S, mgr);
    setBrain(plArmatureBrain::Convert(mgr->ReadCreatable(S)));
}

void plAvPushBrainMsg::write(hsStream* S, plResManager* mgr) {
    plAvTaskMsg::write(S, mgr);
    mgr->WriteCreatable(S, fBrain);
}

void plAvPushBrainMsg::IPrcWrite(pfPrcHelper* prc) {
    plAvTaskMsg::IPrcWrite(prc);

    if (fBrain != NULL) {
        prc->writeSimpleTag("Brain");
        fBrain->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Brain");
        prc->writeParam("NULL", true);
        prc->endTag();
    }
}

void plAvPushBrainMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Brain") {
        if (tag->getParam("NULL", "false").toBool())
            setBrain(NULL);
        else if (tag->hasChildren())
            setBrain(plArmatureBrain::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAvTaskMsg::IPrcParse(tag, mgr);
    }
}

plArmatureBrain* plAvPushBrainMsg::getBrain() const { return fBrain; }

void plAvPushBrainMsg::setBrain(plArmatureBrain* brain) {
    if (fBrain != NULL)
        delete fBrain;
    fBrain = brain;
}


/* plAvPopBrainMsg */
plAvPopBrainMsg::plAvPopBrainMsg() { }
plAvPopBrainMsg::~plAvPopBrainMsg() { }

IMPLEMENT_CREATABLE(plAvPopBrainMsg, kAvPopBrainMsg, plAvTaskMsg)