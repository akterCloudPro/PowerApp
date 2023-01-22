//OnSuccess (save last submitted data in a local variable "varLastSubmittedRec")
Notify("Data saved successfully",NotificationType.Success); UpdateContext({varLastSubmittedRec: Form3.LastSubmit})

// DefaultMode
If(IsBlank(varLastSubmittedRec),FormMode.New, FormMode.View)

//OnSelect (Edit Button)
UpdateContext({lVarEditRec:true}) 

// Make a form Edit based on context 
// DefaultMode
If(
    lVarEditRec And !IsBlank(varLastSubmittedRec),
    FormMode.Edit,
    If(
      IsBlank(varLastSubmittedRec),
      FormMode.New, FormMode.View
    )
)

// Make teh value false after submitting edit form (OnSuccess)
Notify("Data saved successfully",NotificationType.Success); UpdateContext({varLastSubmittedRec: Form3.LastSubmit}); UpdateContext({lVarEditRec:false})

