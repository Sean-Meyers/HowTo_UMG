// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/PanelWidget.h"
//#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"
#include "Components/CanvasPanelSlot.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HowTo_UMGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HOWTO_UMG_API AHowTo_UMGGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:

    // Remove the current menu widget and create a new one from the specified
    // class, if provided.
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        UWidget* new_menu_widget(TSubclassOf<UUserWidget> new_widget_class,
                                               UPanelWidget* widget = nullptr);

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void remove_widget(UUserWidget* widget);

    // Move a widget relative to another (or the same) widget.
    //
    // Parameters:
    //      widget -- The widget to move
    //      relative -- The widget who's position will be factored into the new
    //                  position of the widget to move.
    //      offset -- How much to move the widget by. Added with the position
    //                of relative to determine the final position of 
    //                the widget.
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void widget_move(UWidget* widget, UWidget* relative,
                                                      struct FVector2D offset);

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        FString get_address(UObject* reference);

protected:

    // Called when the game starts
    virtual void BeginPlay() override;

    // The widget class we will use as our menu when the game starts
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    // The widget instance we are using as our menu
    UPROPERTY()
    UUserWidget* CurrentWidget;
    
    UPROPERTY()
        TArray<UUserWidget*> active_widgets;
};
